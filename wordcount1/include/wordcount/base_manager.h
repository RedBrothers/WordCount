#ifndef WORDCOUNT_BASE_MANAGER_H
#define WORDCOUNT_BASE_MANAGER_H

#include <map>
#include <set>
#include <vector>
#include <string>
#include <functional>
#include "typedefs.h"

class BaseManager {
public:
    void save();
    BaseManager(
            std::string out_by_a,
            std::string out_by_n)
        : out_by_a_{ std::move(out_by_a) }
        , out_by_n_{ std::move(out_by_n) } {}
protected:
    // main dictionary
    Dict wc;
private:
    std::string out_by_a_;
    std::string out_by_n_;
};

#endif //WORDCOUNT_BASE_MANAGER_H
