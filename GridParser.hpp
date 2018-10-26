#pragma once
#include "Definitions.hpp"
#include <fstream>
#include <string>

class GridParser
{
public:
    GridParser() = default;

    Grid read(const std::string& filename)
    {
        Grid grid;
        std::string tempLine;
        std::ifstream file(filename);

        while(file)
        {
            std::getline(file, tempLine);
            grid.emplace_back(Grid::value_type(tempLine.cbegin(),
                                               tempLine.cend()));
        }
        return grid;
    }
};
