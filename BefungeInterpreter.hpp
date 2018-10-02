#pragma once
#include <vector>
#include <map>

enum class Direction;
using Position = std::pair<int, int>;

class BefungeInterpreter
{
public:
    BefungeInterpreter();
    void run();
private:
    using Grid = std::vector<std::vector<char>>;
    using Stack = std::vector<int>;

    static const std::map<Direction, Position> movementMatrix;

    Grid grid;
    Stack stack;
    Position currentPosition;
    Direction currentDirection;

    void interpretCharacterOnCurrentPosition();
    void changeDirection(Direction newDirection);
    auto getTwoLastValuesFromStack();
    void add();
    void subtract();
    void multiply();
    void divide();
    void modulo();
    void displayGrid() const;
    void displayStack() const;
};
