#include "Parser.hpp"
#include "BefungeInterpreter.hpp"
#include "GridReader.hpp"

int main()
{
    auto grid{GridReader().read("grid.txt")};
    auto parsedGrid{Parser().parse(grid)};
    BefungeInterpreter interpreter(parsedGrid);
    interpreter.run();
    return 0;
}
