#pragma once
#include "Definitions.hpp"
#include <string>
#include <vector>
#include <cmath>
#include <boost/range/irange.hpp>

class Parser
{
public:
    Parser(const std::string entryGrid)
    : entryGrid(entryGrid)
    {}

    Grid parse()
    {
        auto parsedGridSize{sqrt(entryGrid.size())};
        Grid parsedGrid(parsedGridSize);

        for(auto i : boost::irange(0lu,entryGrid.size()))
        {
            parsedGrid[i/parsedGridSize].push_back(entryGrid[i]);
        }
        return parsedGrid;
    }
private:
    std::string entryGrid;
};
