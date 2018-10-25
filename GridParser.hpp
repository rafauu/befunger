#pragma once
#include "Definitions.hpp"
#include <fstream>
#include <string>

class GridParser
{
public:
    GridParser() = default;

    Grid read(std::string filename)
    {
        Grid grid;
        std::string tempLine;
        std::ifstream file(filename);

        while(file)
        {
            std::getline(file, tempLine);
            Grid::value_type tempVec;
            for(auto ch : tempLine)
            {
                tempVec.push_back(ch);
            }
            grid.push_back(tempVec);
        }
        return grid;
    }
};
