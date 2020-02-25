#include <fstream>
#include <iostream>
#include "base_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

std::string BaseManager::read_file(const std::string &file_name) {
    std::ifstream      in_file;
    std::stringstream  str_stream;
    std::string        file_str;

    in_file.open(file_name);
    str_stream << in_file.rdbuf();
    file_str = str_stream.str();

    return file_str;
}

std::vector<size_t> BaseManager::split_file(const std::string &file, size_t n_chunks) {
    std::vector<size_t>         indices;
    size_t                      estimated_chunk_len;
    auto                        file_length = file.length();

    estimated_chunk_len = static_cast<size_t>( file_length / n_chunks );

    for (size_t i = 0; i < n_chunks; ++i) {
        indices.push_back(i * estimated_chunk_len);
    }
    indices.push_back(file_length);

    for (size_t i = 1; i < indices.size() - 1; ++i) {
        while (indices[i] > 0 && indices[i] > indices[i - 1] && file[indices[i]] != ' ') {
            --indices[i];
        }
        std::cout << indices[i] << std::endl;
    }

    return indices;
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
