#ifndef WORDCOUNT_INDEXER_H
#define WORDCOUNT_INDEXER_H

#include "queue.h"
#include "typedefs.h"

class Indexer {
public:
    Indexer(std::string indir,
            Deque<std::string>& file_queue)
            : indir_{ std::move(indir) }
            , file_queue_{ file_queue } {}

    void run();
private:
    std::string indir_;
    Deque<std::string>& file_queue_;

    void index_dir(const std::string& dir);
};

#endif //WORDCOUNT_INDEXER_H
