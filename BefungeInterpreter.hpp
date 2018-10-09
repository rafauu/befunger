#pragma once
#include "Definitions.hpp"
#include "Position.hpp"

enum class Direction;

class BefungeInterpreter
{
public:
    BefungeInterpreter(Grid grid);
    void run();
private:
    using Stack = std::vector<int>;

    Grid grid;
    Stack stack;
    Position currentPosition;
    Direction currentDirection;

    void interpretCharacterOnCurrentPosition();
    void makeMove(Direction direction);
    void changeDirection(Direction newDirection);
    auto getTwoLastValuesFromStack();
    void changeDirectionHorizontally();
    void changeDirectionVertically();
    void add();
    void subtract();
    void multiply();
    void divide();
    void modulo();
    void displayGrid() const;
    void displayStack() const;
};
