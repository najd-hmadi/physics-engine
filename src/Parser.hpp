#pragma once
#include <fstream>
#include <vector>
#include <filesystem>

#include <cassert>
#include "Classes.hpp"
namespace fs = std::filesystem;
class Parser
{
public:
    std::string source_file;
    std::fstream file;
    Parser();
    std::string find_file();
    std::string trim(const std::string &string);
    std::string parse_params(const std::string &str);
    int str_to_num(const std::string &str);
    std::vector<SceneObject*> parse();
    ~Parser() = default;
};

