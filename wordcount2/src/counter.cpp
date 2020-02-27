#include "wordcount/counter.h"
#include "utils.h"

void Counter::run() {
    while (true) {
        // pop file from file queue
        auto file = std::move(file_queue_.pop_back());

        // check termination condition
        if (file == INDEXING_DONE) {
            // tell other threads to finish
            file_queue_.push_front(file);
            break;
        }

        // process file
        try {
            auto wc = std::move(count_words(file, 0, file.length()));
            // push dict into dict queue
            dict_queue_.push_front(std::move(wc));
        } catch(...) {
            // push the file back to the file queue
            //file_queue_.push_front(std::move(file));
            // or just do nothing ...
        }
    }
}
