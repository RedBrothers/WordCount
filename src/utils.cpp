#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/locale.hpp>

namespace ba = boost::locale::boundary;
namespace lc = boost::locale;

Dict count_words(const std::string& file, size_t start, size_t end) {
    Dict                chunk_map;
    ba::ssegment_index  map(ba::word, file.begin() + start, file.begin() + end);
    map.rule(ba::word_any);

    for (auto it = map.begin(), e = map.end(); it != e; ++it) {

        std::string word(*it);

        word = lc::normalize(word);
        word = lc::fold_case(word);

        ++chunk_map[word];
    }

    return chunk_map;
}

std::string read_file(const std::string &file_name) {
    std::ifstream      in_file;
    std::stringstream  str_stream;
    std::string        file_str;

    in_file.open(file_name);
    str_stream << in_file.rdbuf();
    file_str = str_stream.str();

    return file_str;
}

std::vector<size_t> split_file(const std::string &file, size_t n_chunks) {
    std::vector<size_t>         indices;
    size_t                      estimated_chunk_len;
    auto                        file_length = file.length();

    estimated_chunk_len = static_cast<size_t>( file_length / n_chunks );

    for (size_t i = 0; i < n_chunks; ++i) {
        indices.push_back(i * estimated_chunk_len);
    }
    indices.push_back(file_length);

    for (size_t i = 1; i < indices.size() - 1; ++i) {
        while (indices[i] > 0 && file[indices[i]] != ' ') {
            --indices[i];
        }
    }

    return indices;
}

Dict merge_dicts(const Dict& d1, const Dict& d2) {
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

void save_dict(const std::string &filename, const OrderedDict &d) {
    std::ofstream out(filename);

    if (!out.is_open()) {
        throw std::runtime_error("couldn't open a file " + filename);
    }
    for (auto& t : d) {
        out << t.first << " " << t.second << std::endl;
    }
}

OrderedDict sort_by_a(const Dict& d) {
    OrderedDict v;
    v.reserve(d.size());
    std::copy(d.begin(), d.end(), std::back_inserter(v));
    auto comparator = [](const Tuple& p1, const Tuple& p2) { return p1.first < p2.first; };
    std::sort(v.begin(), v.end(), comparator);
    return v;
}

OrderedDict sort_by_n(const Dict& d) {
    OrderedDict v;
    v.reserve(d.size());
    std::copy(d.begin(), d.end(), std::back_inserter(v));
    auto comparator = [](const Tuple& p1, const Tuple& p2) { return p1.second > p2.second; };
    std::sort(v.begin(), v.end(), comparator);
    return v;
}
