#include <fstream>
#include <iostream>
#include "base_manager.h"

Dict BaseManager::merge_dicts(const Dict& d1, const Dict& d2) {
    Dict result {d1};
    for (auto& [word, count] : d2) {
        auto it = d1.find(word);
        if (it != d1.end()) {
            result[word] += count;
        } else {
            result[word] = count;
        }
    }
    return result;
}

void BaseManager::save_dict(const std::string &filename, const OrderedDict &d) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("couldn't open a file " + filename);
    }
    for (auto& t : d) {
        out << t.first << " " << t.second << std::endl;
    }
}

OrderedDict BaseManager::sort_by_a(const Dict& d) {
    Function comparator = [](
            const Tuple& p1, const Tuple& p2) { return p1.second > p2.second; };
    return OrderedDict(d.begin(), d.end(), comparator);
}

OrderedDict BaseManager::sort_by_n(const Dict& d) {
    Function comparator = [](
            const Tuple& p1, const Tuple& p2) { return p1.second > p2.second; };
    return OrderedDict(d.begin(), d.end(), comparator);
}


