#include "BefungeInterpreter.hpp"
#include <iostream>
#include <iterator>
#include <thread>
#include <algorithm>
#include <random>

enum class Direction
{
    Right,
    Left,
    Up,
    Down,
    DirectionCount
};

BefungeInterpreter::BefungeInterpreter(Grid grid)
: grid{grid}
, output{}
, stack{}
, currentPosition{}
, currentDirection{Direction::Right}
, inputModeStatus{false}
, nextInstructionShouldBeIgnored{false}
{}

BefungeInterpreter::~BefungeInterpreter() = default;

void BefungeInterpreter::run()
{
    while(true)
    {
        displayStack();
        displayGrid();
        displayOutput();

        interpretCharacterOnCurrentPosition();
        makeMove(currentDirection);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    };
}

void BefungeInterpreter::interpretCharacterOnCurrentPosition()
{
    const auto& [x, y] = currentPosition;
    auto ch = grid.at(x).at(y);

    if(' ' == ch and not inputModeStatus)
    {
        return;
    }

    if('"' == ch)
    {
        toggleInputModeStatus();
        return;
    }

    if(nextInstructionShouldBeIgnored)
    {
        nextInstructionShouldBeIgnored = false;
        return;
    }

    if(inputModeStatus)
    {
        stack.push_back(ch);
        return;
    }

    if(isdigit(ch))
    {
        stack.push_back(ch-'0');
        return;
    }

    switch(ch)
    {
        case '>': changeDirection(Direction::Right);                         break;
        case '<': changeDirection(Direction::Left);                          break;
        case '^': changeDirection(Direction::Up);                            break;
        case 'v': changeDirection(Direction::Down);                          break;
        case '?': chooseRandomDirection();                                   break;
        case '#': ignoreNextInstruction();                                   break;
        case '@': exit(EXIT_SUCCESS);

        case '_': changeDirectionHorizontally();                             break;
        case '|': changeDirectionVertically();                               break;

        case '+': add();                                                     break;
        case '-': subtract();                                                break;
        case '*': multiply();                                                break;
        case '/': divide();                                                  break;
        case '%': modulo();                                                  break;
        case '!': negation();                                                break;
        case '`': firstIsGreaterThanSecond();                                break;
        case ':': doubleLastNumberOnStack();                                 break;
        case '\\':swapTwoLastElements();                                     break;
        case '$': discardLastElementFromStack();                             break;

        case '.': printNumberFromStack();                                    break;
        case ',': printCharFromStack();                                      break;
        case '&': inputAsNumber();                                           break;
        case '~': inputAsChar();                                             break;

        case 'g': getSignFromGridUsingTwoLastValuesFromStackAsCoordinates(); break;
        case 'p': putSignToGridUsingTwoLastValuesFromStackAsCoordinates();   break;

        default: break;
    }
}

void BefungeInterpreter::makeMove(Direction direction)
{
    switch(direction)
    {
        case Direction::Right: currentPosition += { 0, 1}; break;
        case Direction::Left:  currentPosition += { 0,-1}; break;
        case Direction::Up:    currentPosition += {-1, 0}; break;
        case Direction::Down:  currentPosition += { 1, 0}; break;
        default: break;
    }
    if(currentPosition.x == -1) currentPosition.x = grid.size() - 1;
    if(currentPosition.y == -1) currentPosition.y = grid[0].size() - 1;
    if(currentPosition.x == grid.size()) currentPosition.x = 0;
    if(currentPosition.y == grid[0].size()) currentPosition.y = 0;
}

void BefungeInterpreter::changeDirection(Direction newDirection)
{
    currentDirection = newDirection;
}

void BefungeInterpreter::chooseRandomDirection()
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, static_cast<int>(Direction::DirectionCount)-1);

    currentDirection = static_cast<Direction>(dist(rng));
}

void BefungeInterpreter::ignoreNextInstruction()
{
    nextInstructionShouldBeIgnored = true;
}

auto BefungeInterpreter::getValueFromStackAndPopIt()
{
    auto value = stack.back();
    stack.pop_back();
    return value;
}

auto BefungeInterpreter::getTwoLastValuesFromStack()
{
    auto num1 = getValueFromStackAndPopIt();
    auto num2 = getValueFromStackAndPopIt();
    return std::make_pair(num1, num2);
}

void BefungeInterpreter::changeDirectionHorizontally()
{
    if(getValueFromStackAndPopIt())
    {
        changeDirection(Direction::Left);
    }
    else
    {
        changeDirection(Direction::Right);
    }
}

void BefungeInterpreter::changeDirectionVertically()
{
    if(getValueFromStackAndPopIt())
    {
        changeDirection(Direction::Up);
    }
    else
    {
        changeDirection(Direction::Down);
    }
}

void BefungeInterpreter::add()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    stack.push_back(num2 + num1);
}

void BefungeInterpreter::subtract()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    stack.push_back(num2 - num1);
}

void BefungeInterpreter::multiply()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    stack.push_back(num2 * num1);
}

void BefungeInterpreter::divide()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    stack.push_back(num2 / num1);
}

void BefungeInterpreter::modulo()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    stack.push_back(num2 % num1);
}

void BefungeInterpreter::negation()
{
    if(getValueFromStackAndPopIt())
    {
        stack.push_back(0);
    }
    else
    {
        stack.push_back(1);
    }
}

void BefungeInterpreter::firstIsGreaterThanSecond()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    if(num2 > num1)
    {
        stack.push_back(1);
    }
    else
    {
        stack.push_back(0);
    }
}

void BefungeInterpreter::doubleLastNumberOnStack()
{
    stack.push_back(stack.back());
}

void BefungeInterpreter::swapTwoLastElements()
{
    auto [num1, num2] = getTwoLastValuesFromStack();
    stack.push_back(num1);
    stack.push_back(num2);
}

void BefungeInterpreter::discardLastElementFromStack()
{
    stack.pop_back();
}

void BefungeInterpreter::toggleInputModeStatus()
{
    inputModeStatus ^= true;
}

void BefungeInterpreter::printNumberFromStack()
{
    output += std::to_string(getValueFromStackAndPopIt());
}

void BefungeInterpreter::printCharFromStack()
{
    output += static_cast<char>(getValueFromStackAndPopIt());
}

void BefungeInterpreter::inputAsNumber()
{
    Stack::value_type num;
    std::cin >> num;
    stack.push_back(num);
}

void BefungeInterpreter::inputAsChar()
{
    Grid::value_type::value_type ch;
    std::cin >> ch;
    stack.push_back(ch);
}

void BefungeInterpreter::getSignFromGridUsingTwoLastValuesFromStackAsCoordinates()
{
    auto [x, y] = getTwoLastValuesFromStack();
    stack.push_back(grid[x][y]);
}

void BefungeInterpreter::putSignToGridUsingTwoLastValuesFromStackAsCoordinates()
{
    auto [x, y] = getTwoLastValuesFromStack();
    auto ch = getValueFromStackAndPopIt();
    grid[x][y] = ch;
}

void BefungeInterpreter::displayGrid() const
{
    for(auto i=0; i<grid.size(); ++i)
    {
        for(auto j=0; j<grid[i].size(); ++j)
        {
            auto ch = grid[i][j];
            Position(i, j) == currentPosition ? std::cout << "\033[7m" << ch << "\033[0m"
                                              : std::cout << ch;
        }
        std::cout << std::endl;
    }
}

void BefungeInterpreter::displayStack() const
{
    std::cout << "Stack: ";
    std::copy(stack.cbegin(),
              stack.cend(),
              std::ostream_iterator<Stack::value_type>(std::cout, " "));
    std::cout << std::endl;
}

void BefungeInterpreter::displayOutput() const
{
    std::cout << "Output: " << output << std::endl;
}
