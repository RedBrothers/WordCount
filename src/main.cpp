#include "wordcount/config.h"
#include "wordcount/simple_manager.h"
#include <string>
#include <chrono>
#include <iostream>
#include <boost/locale.hpp>

int main(int argc, char* argv[]) {

    // parse a config file
    std::string filename;
    if (argc != 2) {
        filename = "config.dat";
    } else {
        filename = std::string(argv[1]);
    }
    ConfigParser parser(filename);
    std::string infile = parser.get("infile");
    std::string out_by_a = parser.get("out_by_a");
    std::string out_by_n = parser.get("out_by_n");
    size_t n_threads = std::stoul(parser.get("threads"));

    SimpleManager manager{infile, out_by_a, out_by_n, n_threads};
    
    // Configure locale
    std::locale         loc = boost::locale::generator().generate("en_US.UTF-8");
    std::locale::global(loc);

    // Start execution
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

    // Display execution time
    std:: cout
        << "Reading: " << reading.count() << std::endl
        << "Counting: " << counting.count() << std::endl
        << "Total: " << total.count() << std::endl;

    return 0;
}
