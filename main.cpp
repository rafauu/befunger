#include "Parser.hpp"
#include "BefungeInterpreter.hpp"
#include "GridReader.hpp"

int main(int argc, char* argv[])
{
    auto grid{GridReader().read(argv[1])};
    auto parsedGrid{Parser().parse(grid)};
    BefungeInterpreter interpreter(parsedGrid);
    interpreter.run();
    return 0;
}
