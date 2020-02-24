#ifndef WORDCOUNT_BASE_MANAGER_H
#define WORDCOUNT_BASE_MANAGER_H

#include <map>
#include <set>
#include <vector>
#include <string>
#include <functional>
#include "counter.h"
#include "typedefs.h"

// provides utilities for managers implementations
class BaseManager {
protected:
    // main dictionary
    Dict wc;

    // file manipulations
    static std::string read_file(const std::string& filename);
    static std::vector<std::string> split_file(const std::string& file, size_t n_chunks);

    // dict manipulations
    static Dict merge_dicts(const Dict& d1, const Dict& d2);
    static void save_dict(const std::string& filename, const OrderedDict & d);
    static OrderedDict sort_by_a(const Dict& d);
    static OrderedDict sort_by_n(const Dict& d);
};

#endif //WORDCOUNT_BASE_MANAGER_H
