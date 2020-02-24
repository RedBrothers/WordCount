#include "base_manager.h"


using Tuple = std::pair<std::string, size_t>;

void WordCounter::save(const std::string &filename, bool alpha) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("couldn't open a file " + filename);
    }
    using Function = std::function<bool(Tuple, Tuple)>;
    Function comparator;
    if (alpha) {
        comparator = [](const Tuple& p1, const Tuple& p2) { return p1.first < p2.first; };
    } else {
        comparator = [](const Tuple& p1, const Tuple& p2) { return p1.second > p2.second; };
    }
    std::set<Tuple, Function> sorted (counts.begin(), counts.end(), comparator);
    for (auto& t : sorted) {
        out << t.first << " " << t.second << std::endl;
    }
}