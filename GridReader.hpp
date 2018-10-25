#pragma once
#include <fstream>
#include <string>

class GridReader
{
public:
    GridReader() = default;

    std::vector<std::string> read(std::string filename)
    {
        std::vector<std::string> grid;
        std::string tempLine;
        std::ifstream file(filename);

        while(file)
        {
            std::getline(file, tempLine);
            grid.push_back(tempLine);
        }
        return grid;
    }
};
