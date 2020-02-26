#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/locale.hpp>
#include <boost/filesystem.hpp>
#include <archive.h>
#include <archive_entry.h>

namespace ba = boost::locale::boundary;
namespace lc = boost::locale;

Dict        count_words(const std::string& file, size_t start, size_t end) {
    Dict                chunk_map;
    ba::ssegment_index  map(ba::word, file.begin() + start, file.begin() + end);
    map.rule(ba::word_letters);

    for (auto it = map.begin(), e = map.end(); it != e; ++it) {

        std::string word(*it);

        word = lc::normalize(word);
        word = lc::fold_case(word);

        ++chunk_map[word];
    }

    return chunk_map;
}

bool       is_archive(const std::string &file_name) {
    std::vector<std::string> extensions = {".zip", ".tar", ".tar.gz", ".gz", ".7z"};

    return std::find(
            extensions.begin(),
            extensions.end(),
            boost::locale::to_lower(boost::filesystem::extension(file_name))
            ) != extensions.end();

}

bool       is_text_file(const std::string &file_name) {
    std::vector<std::string> extensions = {".txt"};

    return std::find(
            extensions.begin(),
            extensions.end(),
            boost::locale::to_lower(boost::filesystem::extension(file_name))
    ) != extensions.end();

}

std::string read_archive(const std::string &file_name) {
    std::stringstream           ss;
    std::vector<std::string>    vs;
    struct archive              *a;
    struct archive_entry        *entry;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if (archive_read_open_filename(a, file_name.c_str(), 10240) != ARCHIVE_OK)
        exit(1);

    if (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        la_int64_t  entry_size = archive_entry_size(entry);

        if (archive_entry_filetype(entry) == AE_IFREG) {
            char *buff = new char[entry_size];
            archive_read_data(a, buff, entry_size);

            ss << buff;

            delete[] buff;
        }
    }

    if (archive_read_free(a) != ARCHIVE_OK)
        exit(1);

    return ss.str();
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
    // maybe we don't need a copy?
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
