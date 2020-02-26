#ifndef WORDCOUNT_SIMPLE_MANAGER_H
#define WORDCOUNT_SIMPLE_MANAGER_H

#include <string>
#include <vector>
#include "base_manager.h"

class SimpleManager : public BaseManager {
public:
    SimpleManager(
            std::string infile,
            std::string out_by_a,
            std::string out_by_n,
            size_t n_threads)
            : BaseManager{ out_by_a, out_by_n }
            , infile {std::move(infile) }
            , out_by_a { std::move(out_by_a) }
            , out_by_n { std::move(out_by_n) }
            , n_threads { n_threads } {}
    void read();
    void count();
private:
    std::string infile;
    std::string out_by_a;
    std::string out_by_n;
    size_t n_threads;
    std::string file;
};

#endif //WORDCOUNT_SIMPLE_MANAGER_H
