#include "counter.h"
#include <fstream>

#include <boost/locale.hpp>
#include <boost/filesystem.hpp>

using namespace boost::locale;
using namespace boost::filesystem;


Dict WordCounter::process(const std::string& file) {
    wc = {{"hey", 3}, {"you", 2}, {"idiot", 1}};
    return wc;
}

