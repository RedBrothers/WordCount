#ifndef WORDCOUNT_MERGER_H
#define WORDCOUNT_MERGER_H

#include "queue.h"
#include "typedefs.h"
#include <thread>
#include <mutex>

class Merger {
public:
    Merger(Deque<Dict>& dict_queue, std::mutex& m)
        : dict_queue_{ dict_queue }, m_{ m } {}
    void run();
private:
    Deque<Dict>& dict_queue_;
    std::mutex& m_; // for double-popping
};

#endif //WORDCOUNT_MERGER_H
