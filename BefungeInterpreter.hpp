#pragma once
#include "Definitions.hpp"
#include "Position.hpp"

enum class Direction;

class BefungeInterpreter
{
public:
    BefungeInterpreter(Grid grid);
    ~BefungeInterpreter();
    void run();
private:
    using Stack = std::vector<int>;

    Grid grid;
    Stack stack;
    Position currentPosition;
    Direction currentDirection;
    bool inputModeStatus;
    bool nextInstructionShouldBeIgnored;

    void interpretCharacterOnCurrentPosition();
    void makeMove(Direction direction);
    void changeDirection(Direction newDirection);
    void chooseRandomDirection();
    void ignoreNextInstruction();
    auto getValueFromStackAndPopIt();
    auto getTwoLastValuesFromStack();
    void changeDirectionHorizontally();
    void changeDirectionVertically();
    void add();
    void subtract();
    void multiply();
    void divide();
    void modulo();
    void negation();
    void firstIsGreaterThanSecond();
    void doubleLastNumberOnStack();
    void swapTwoLastElements();
    void discardLastElementFromStack();
    void toggleInputModeStatus();
    void printNumberFromStack();
    void printCharFromStack();

    void displayGrid() const;
    void displayStack() const;
};
