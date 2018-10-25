#include "BefungeInterpreter.hpp"
#include "GridParser.hpp"

int main(int argc, char* argv[])
{
    auto grid{GridParser().read(argv[1])};
    BefungeInterpreter interpreter(grid);
    interpreter.run();
    return 0;
}
