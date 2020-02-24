#include "config.h"
#include "counter.h"
#include "base_manager.h"
#include <string>
#include <iostream>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        throw std::runtime_error("Expected call: ./wordcount [config_path]");
    }
    std::string filename{argv[1]};
    ConfigParser parser(filename);
    std::string infile = parser.get("infile");
    std::string out_by_a = parser.get("out_by_a");
    std::string out_by_n = parser.get("out_by_n");
    // size_t threads = std::stoul(parser.get("threads"));

    SingleThreadManager manager;
    WordCounter counter;
    counter.read(infile);


    counter.save(out_by_a, true);
    counter.save(out_by_n);
    return 0;
}
