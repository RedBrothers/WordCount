#ifndef WORDCOUNT_TYPEDEFS_H
#define WORDCOUNT_TYPEDEFS_H

#include <set>
#include <map>
#include <string>
#include <vector>
#include <functional>

// not sure whether name injections into
// client code is a good practice
using Dict = std::map<std::string, size_t>;
using Tuple = std::pair<std::string, size_t>;
using OrderedDict = std::vector<Tuple>;

#endif //WORDCOUNT_TYPEDEFS_H
