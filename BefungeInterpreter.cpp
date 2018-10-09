#include "Parser.hpp"
#include "BefungeInterpreter.hpp"
#include <iostream>
#include <utility>
#include <chrono>
#include <thread>
#include <cctype>
#include <cstdlib>

enum class Direction
{
    Right,
    Left,
    Up,
    Down
};

BefungeInterpreter::BefungeInterpreter(Grid grid)
: grid{grid}
, stack{}
, currentPosition{}
, currentDirection{Direction::Right}
{}

void BefungeInterpreter::run()
{
    while(true)
    {
        displayGrid();
        displayStack();
        interpretCharacterOnCurrentPosition();
        makeMove(currentDirection);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };
}

void BefungeInterpreter::interpretCharacterOnCurrentPosition()
{
    const auto& [x, y] = currentPosition;
    char ch = grid[x][y];
    if(isxdigit(ch)) stack.push_back(ch-'0');
    switch(ch)
    {
        case ' ': /*nop*/                            break;
        case '>': changeDirection(Direction::Right); break;
        case '<': changeDirection(Direction::Left);  break;
        case '^': changeDirection(Direction::Up);    break;
        case 'v': changeDirection(Direction::Down);  break;
        case '?': /*tbd*/                            break;
        case '#': /*tbd*/                            break;
        case '@': exit(EXIT_SUCCESS);

        case '_': /*tbd*/                            break;
        case '|': /*tbd*/                            break;

        case '+': add();                             break;
        case '-': subtract();                        break;
        case '*': multiply();                        break;
        case '/': divide();                          break;
        case '%': modulo();                          break;
        case '!': /*tbd*/                            break;
        case '`': /*tbd*/                            break;
        case ':': /*tbd*/                            break;
        case '\\': /*tbd*/                           break;
        case '$': /*tbd*/                            break;
    }
}

void BefungeInterpreter::makeMove(Direction direction)
{
    switch(direction)
    {
        case Direction::Right: currentPosition += Position{ 0, 1}; break;
        case Direction::Left:  currentPosition += Position{ 0,-1}; break;
        case Direction::Up:    currentPosition += Position{-1, 0}; break;
        case Direction::Down:  currentPosition += Position{ 1, 0}; break;
    }
}

void BefungeInterpreter::changeDirection(Direction newDirection)
{
    currentDirection = newDirection;
}

auto BefungeInterpreter::getTwoLastValuesFromStack()
{
    auto num1 = stack.back();
    stack.pop_back();
    auto num2 = stack.back();
    stack.pop_back();
    return std::make_pair(num1, num2);
}

void BefungeInterpreter::add()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    stack.push_back(num1 + num2);
}

void BefungeInterpreter::subtract()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    stack.push_back(num1 - num2);
}

void BefungeInterpreter::multiply()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    stack.push_back(num1 * num2);
}

void BefungeInterpreter::divide()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    stack.push_back(num1 / num2);
}

void BefungeInterpreter::modulo()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    stack.push_back(num1 % num2);
}

void BefungeInterpreter::displayGrid() const
{
    for(auto i=0; i<grid.size(); ++i)
    {
        for(auto j=0; j<grid[i].size(); ++j)
        {
            std::cout << (Position(i,j) == currentPosition ? "\033[7m" : "\033[0m")
                      << grid[i][j] << "\033[0m";
        }
        std::cout << std::endl;
    }
}

void BefungeInterpreter::displayStack() const
{
    std::cout << "Stack: ";
    for(const auto& el : stack)
        std::cout << el << " ";
    std::cout << std::endl << std::endl;
}
