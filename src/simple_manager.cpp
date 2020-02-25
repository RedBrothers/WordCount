#include "wordcount/simple_manager.h"
#include "utils.h"
#include <thread>
#include <numeric>

void SimpleManager::read() {
    file = std::move(read_file(infile));
}

void SimpleManager::count() {
    if (n_threads == 1) {

        wc = std::move(count_words(file, 0, file.length()));
    } else {
        std::vector<size_t> indices = std::move(split_file(file, n_threads));

        std::vector<Dict> dicts;
        dicts.reserve(n_threads);

        auto fn = [&](size_t i) { dicts[i] = std::move(count_words(file, indices[i], indices[i+1])); };

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
