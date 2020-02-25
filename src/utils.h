#ifndef WORDCOUNT_UTILS_H
#define WORDCOUNT_UTILS_H

#include "typedefs.h"
#include <vector>
#include <string>

// file manipulations
std::string read_file(const std::string& filename);
std::vector<size_t> split_file(const std::string& file, size_t n_chunks);

// word counting
Dict count_words(const std::string& filename, size_t start, size_t end);

// dict manipulations
Dict merge_dicts(const Dict& d1, const Dict& d2);
void save_dict(const std::string& filename, const OrderedDict & d);
OrderedDict sort_by_a(const Dict& d);
OrderedDict sort_by_n(const Dict& d);

#endif //WORDCOUNT_UTILS_H
