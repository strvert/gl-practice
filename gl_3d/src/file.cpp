#include "file.h"
#include <cstdint>
#include <iterator>
#include <fstream>
#include <iostream>
std::string File::Read(std::string filename)
{
    std::ifstream ifs(filename);
    std::string data(
            std::istreambuf_iterator<char>(ifs),
            {}
    );
    return data;
}
