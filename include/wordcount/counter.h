#ifndef WORDCOUNT_COUNTER_H
#define WORDCOUNT_COUNTER_H

#include "queue.h"
#include "typedefs.h"

class Counter {
public:
    Counter(Queue<std::string>& file_queue,
            Queue<Dict>& dict_queue)
            : file_queue_{ file_queue }
            , dict_queue_{ dict_queue } {}
    void run();
private:
    Queue<std::string>& file_queue_;
    Queue<Dict>& dict_queue_;
};

#endif //WORDCOUNT_COUNTER_H
