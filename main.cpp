#include "config.h"
#include "simple_manager.h"
#include <string>
#include <chrono>
#include <iostream>

int main(int argc, char* argv[]) {

    // parse a config file
    if (argc != 2) {
        throw std::runtime_error("Expected call: ./wordcount [config_path]");
    }
    std::string filename{argv[1]};
    ConfigParser parser(filename);
    std::string infile = parser.get("infile");
    std::string out_by_a = parser.get("out_by_a");
    std::string out_by_n = parser.get("out_by_n");
    size_t n_threads = std::stoul(parser.get("threads"));

    SimpleManager manager{infile, out_by_a, out_by_n, n_threads};

    // start execution
    auto start = std::chrono::high_resolution_clock::now();

    auto r_start = std::chrono::high_resolution_clock::now();
    manager.read();
    auto r_end = std::chrono::high_resolution_clock::now();

    auto c_start = std::chrono::high_resolution_clock::now();
    manager.count();
    auto c_end = std::chrono::high_resolution_clock::now();

    manager.save();
    auto end = std::chrono::high_resolution_clock::now();

    auto total = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    auto reading = std::chrono::duration_cast<std::chrono::seconds>(r_end - r_start);
    auto counting = std::chrono::duration_cast<std::chrono::seconds>(c_end - c_start);

    // display execution time
    std:: cout
        << "Reading: " << reading.count() << std::endl
        << "Counting: " << counting.count() << std::endl
        << "Total: " << total.count() << std::endl;

    return 0;
}
