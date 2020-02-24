#ifndef WORDCOUNT_COUNTER_H
#define WORDCOUNT_COUNTER_H

#include <map>
#include <string>
#include "typedefs.h"

class WordCounter {
public:
    Dict process(const std::string& file, size_t start, size_t end);
private:
    Dict wc;
};

#endif //WORDCOUNT_COUNTER_H
