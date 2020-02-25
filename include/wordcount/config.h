#ifndef LAB5_TEXT_CONFIG_H
#define LAB5_TEXT_CONFIG_H


#include <map>
#include <string>
#include <sstream>
#include <fstream>


class ConfigParser {
public:
    explicit ConfigParser(const std::string& filename);
    [[nodiscard]] std::string get(const std::string& key) const { return options.at(key); }
private:
    std::map<std::string, std::string> options;
    void parse(std::ifstream& file);
};

#endif //LAB5_TEXT_CONFIG_H
