#include "simple_manager.h"
#include <thread>
#include <numeric>

void SimpleManager::read() {
    file = std::move(read_file(in));
}

void SimpleManager::count() {
    if (n_threads == 1) {
        WordCounter counter;
        wc = std::move(counter.process(file));
    } else {
        std::vector<std::string> chunks = std::move(split_file(file, n_threads));

        std::vector<Dict> dicts;
        dicts.reserve(n_threads);

        std::vector<WordCounter> counters{n_threads};
        auto fn = [&](size_t i) { dicts[i] = std::move(counters[i].process(chunks[i])); };

        // launching parallel tasks
        std::vector<std::thread> threads;
        threads.reserve(n_threads);
        for (auto i = 0; i < n_threads; ++i) {
            threads.emplace_back(fn, i);
        }

        // wait for threads to finish
        for (auto& t : threads) {
            t.join();
        }

        // naively merge all dicts into one dict
        wc = std::accumulate(dicts.begin(), dicts.end(), Dict{}, merge_dicts);
    }
}

void SimpleManager::save() {
    auto wc_by_a = sort_by_a(wc);
    save_dict(out_by_a, wc_by_a);
    auto wc_by_n = sort_by_n(wc);
    save_dict(out_by_n, wc_by_n);
}
