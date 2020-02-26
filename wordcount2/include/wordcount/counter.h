#ifndef WORDCOUNT_COUNTER_H
#define WORDCOUNT_COUNTER_H

#include "queue.h"
#include "typedefs.h"

class Counter {
public:
    Counter(Deque<std::string>& file_queue,
            Deque<Dict>& dict_queue)
            : file_queue_{ file_queue }
            , dict_queue_{ dict_queue } {}
    void run();
private:
    Deque<std::string>& file_queue_;
    Deque<Dict>& dict_queue_;
};

#endif //WORDCOUNT_COUNTER_H
