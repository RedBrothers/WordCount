#ifndef WORDCOUNT_INDEXER_H
#define WORDCOUNT_INDEXER_H

#include "queue.h"
#include "typedefs.h"

class Indexer {
public:
    Indexer(std::string indir,
            Queue<std::string>& file_queue)
            : indir_{ std::move(indir) }
            , file_queue_{ file_queue } {}
    void run();
private:
    std::string indir_;
    Queue<std::string>& file_queue_;
};

#endif //WORDCOUNT_INDEXER_H
