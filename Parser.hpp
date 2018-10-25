#pragma once
#include "Definitions.hpp"
#include <string>
#include <boost/range/irange.hpp>

class Parser
{
public:
    Parser() = default;

    Grid parse(const std::vector<std::string> entryGrid)
    {
        Grid parsedGrid(entryGrid.size());
        for(auto i : boost::irange(0lu, parsedGrid.size()))
        {
            for(const auto& sign : entryGrid[i])
            {
                parsedGrid[i].push_back(sign);
            }
        }
        return parsedGrid;
    }
};
