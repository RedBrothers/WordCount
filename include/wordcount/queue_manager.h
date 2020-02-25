#ifndef WORDCOUNT_QUEUE_MANAGER_H
#define WORDCOUNT_QUEUE_MANAGER_H

#include "wordcount/base_manager.h"
#include "wordcount/queue.h"
#include "wordcount/indexer.h"
#include "wordcount/counter.h"
#include "wordcount/merger.h"

class QueueManager : BaseManager {
public:
    QueueManager(
            std::string indir,
            std::string out_by_a,
            std::string out_by_n,
            size_t n_count_threads,
            size_t n_merge_threads);
    void run();
    void save();
private:
    Queue<std::string> file_queue_;
    Queue<Dict> dict_queue_;

    Indexer indexer;
    std::vector<Counter> counters;
    std::vector<Merger> mergers;

    std::string out_by_a;
    std::string out_by_n;
};

#endif //WORDCOUNT_QUEUE_MANAGER_H
