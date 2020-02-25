#ifndef WORDCOUNT_MERGER_H
#define WORDCOUNT_MERGER_H

#include "queue.h"
#include "typedefs.h"

class Merger {
public:
    Merger(Queue<Dict>& dict_queue) : dict_queue_{ dict_queue } {}
    void run();
private:
    Queue<Dict>& dict_queue_;
};

#endif //WORDCOUNT_MERGER_H
