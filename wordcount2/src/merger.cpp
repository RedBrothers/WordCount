#include "wordcount/merger.h"
#include "utils.h"

void Merger::run() {
    while (true) {
        std::unique_lock lock{ m_ };
        auto d1 = std::move(dict_queue_.pop_back());
        auto d2 = std::move(dict_queue_.pop_back());
        lock.unlock();

        // check termination condition
        // tell other threads to finish
        // ensure that COUNTING_DONE is
        // in front of the deque
        if (d2 == COUNTING_DONE) {
            dict_queue_.push_back(std::move(d1));
            dict_queue_.push_front(d2);
            break;
        } else if (d1 == COUNTING_DONE) {
            dict_queue_.push_front(d1);
            dict_queue_.push_back(std::move(d2));
            // no break here
            continue;
        }

        auto d = std::move(merge_dicts(d1, d2));
        dict_queue_.push_back(std::move(d));
    }
}
