#include "wordcount/config.h"
#include "wordcount/queue_manager.h"
#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <boost/locale.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char* argv[]) {

    // parse a config file
    std::string filename;
    if (argc != 2) {
        filename = "config.dat";
    } else {
        filename = std::string(argv[1]);
    }
    if (!boost::filesystem::exists(filename) || !boost::filesystem::is_regular_file(filename)) {
        std::cout << "Config file " << filename << " is not valid !" << std::endl;
        return 1;
    }

    ConfigParser parser(filename);
    std::string indir = parser.get("indir");

    if (!boost::filesystem::exists(indir) || !boost::filesystem::is_directory(indir)) {
        std::cout << "Error in config.dat: infile=" << indir << " is not a valid directory !" << std::endl;
        return 1;
    }

    std::string out_by_a = parser.get("out_by_a");
    std::string out_by_n = parser.get("out_by_n");
    size_t n_count_threads = std::stoul(parser.get("count_threads"));
    size_t n_merge_threads = std::stoul(parser.get("merge_threads"));

    std::locale         loc = boost::locale::generator().generate("en_US.UTF-8");
    std::locale::global(loc);

    QueueManager manager{indir, out_by_a, out_by_n, n_count_threads, n_merge_threads};


    // start execution
    auto start = std::chrono::high_resolution_clock::now();
    manager.run();
    auto end = std::chrono::high_resolution_clock::now();

    manager.save();

    typedef std::chrono::duration<float> float_seconds;
    auto total = std::chrono::duration_cast<float_seconds>(end - start);

    // display execution time
    std:: cout
        << std::setprecision(3) << std::fixed
        << "Counting done in " << total.count() << " seconds\n";

    return 0;
}
