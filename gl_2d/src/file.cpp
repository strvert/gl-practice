#include "file.h"
#include <cstdint>
#include <iterator>
#include <fstream>
#include <iostream>

File::File(std::string FileName)
{
    Ifs = std::ifstream(FileName);
    if (Ifs.fail())
    {
        std::cerr << "(" << FileName << ")のオープンに失敗しました" << std::endl;
    }
}

std::vector<std::uint8_t> File::Read()
{
    return std::vector<std::uint8_t>(
                std::istreambuf_iterator<char>(this->Ifs),
                std::istreambuf_iterator<char>()
            );
}

FileTypes File::Type()
{
    FileTypes Type;

    for (auto& magicNumber: this->MagicNumbers)
    {
        for (auto& signature: magicNumber.second)
        {
            Ifs.seekg(std::ios::beg);
            for (auto& number: signature)
            {
                char c;
                Ifs.get(c);
                if (std::uint8_t(c) != number)
                {
                    break;
                }

                if (signature.size() == Ifs.tellg())
                {
                    Ifs.seekg(std::ios::beg);
                    return magicNumber.first;
                }
            }
        }
    }

    Ifs.seekg(std::ios::beg);
    return FileTypes::UNKNOWN;
}
