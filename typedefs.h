#ifndef WORDCOUNT_TYPEDEFS_H
#define WORDCOUNT_TYPEDEFS_H

// not sure whether name injections into
// client code is a good practice
using Dict = std::map<std::string, size_t>;
using Tuple = std::pair<std::string, size_t>;
using Function = std::function<bool(Tuple, Tuple)>;
using OrderedDict = std::set<Tuple, Function>;

#endif //WORDCOUNT_TYPEDEFS_H
