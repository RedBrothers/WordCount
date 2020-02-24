#ifndef WORDCOUNT_COUNTER_H
#define WORDCOUNT_COUNTER_H

#include <map>
#include <string>

using Dict = std::map<std::string, size_t>;

class WordCounter {
public:
	// TODO: implement WordCounter::process
    Dict process(const std::string& file);
private:
    Dict wc;
};

#endif //WORDCOUNT_COUNTER_H
