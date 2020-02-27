#include "utils.h"
#include "wordcount/queue_manager.h"
#include <thread>

QueueManager::QueueManager(
        std::string indir,
        std::string out_by_a,
        std::string out_by_n,
        size_t n_count_threads,
        size_t n_merge_threads)
        : BaseManager{ std::move(out_by_a), std::move(out_by_n) }
        , out_by_a { std::move(out_by_a) }
        , out_by_n { std::move(out_by_n) }
        , indexer { std::move(indir), file_queue_ }
        , counters { n_count_threads, Counter{ file_queue_, dict_queue_ } }
        , mergers { n_merge_threads, Merger{ dict_queue_, m_ } } {
    // for successful termination
    // in case of empty directory
    dict_queue_.push_back({});
}

void QueueManager::run() {
    // launch indexing
    std::thread index_thread (&Indexer::run, indexer);

    // launch counting
    std::vector<std::thread> count_threads;
    count_threads.reserve(counters.size());
    for (auto& c : counters) {
        count_threads.emplace_back(&Counter::run, &c);
    }

    // launch merging
    std::vector<std::thread> merge_threads;
    merge_threads.reserve(mergers.size());
    for (auto& m : mergers) {
        merge_threads.emplace_back(&Merger::run, &m);
    }

    // wait for all threads to finish and
    // "signal" next workers about it
    index_thread.join();
    file_queue_.push_front(INDEXING_DONE);
    for (auto& t : count_threads) t.join();
    dict_queue_.push_front(COUNTING_DONE);
    for (auto& t : merge_threads) t.join();

    // collect the result
    wc = dict_queue_.pop_back();
}

