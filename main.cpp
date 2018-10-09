#include "Parser.hpp"
#include "BefungeInterpreter.hpp"

int main()
{
    const std::string grid{" >>v"
                           "@v77"
                           "@v74"
                           "^<+<"};
    Parser parser(grid);
    auto parsedGrid = parser.parse();
    BefungeInterpreter interpreter(parsedGrid);
    interpreter.run();
    return 0;
}
