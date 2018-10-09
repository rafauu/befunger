#pragma once
#include "Definitions.hpp"
#include "Position.hpp"
#include <vector>
#include <map>

enum class Direction;

class BefungeInterpreter
{
public:
    BefungeInterpreter(Grid grid);
    void run();
private:
    using Stack = std::vector<int>;

 //   static const std::map<Direction, Position> movementMatrix;

    Grid grid;
    Stack stack;
    Position currentPosition;
    Direction currentDirection;

    void interpretCharacterOnCurrentPosition();
    void makeMove(Direction direction);
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
