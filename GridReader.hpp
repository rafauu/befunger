#pragma once
#include <fstream>
#include <string>

class GridReader
{
public:
    GridReader() = default;
    std::string read(std::string filename)
    {
        std::string grid, tempLine;
        std::ifstream file(filename);
        while(file)
        {
            std::getline(file, tempLine);
            grid += tempLine;
        }
        return grid;
    }
};
