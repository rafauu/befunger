#pragma once
#include "Definitions.hpp"
#include <string>
#include <cmath>
#include <boost/range/irange.hpp>

class Parser
{
public:
    Parser() = default;

    Grid parse(const std::string entryGrid)
    {
        auto parsedGridSize{sqrt(entryGrid.size())};
        Grid parsedGrid(parsedGridSize);

        for(auto i : boost::irange(0lu, entryGrid.size()))
        {
            parsedGrid[i/parsedGridSize].push_back(entryGrid[i]);
        }
        return parsedGrid;
    }
};
