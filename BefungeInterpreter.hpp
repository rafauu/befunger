#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <chrono>
#include <thread>
#include <cctype>
#include <cstdlib>


using Position = std::pair<int, int>;
Position& operator+=(Position& lhs, const Position& rhs)
{
    lhs = std::make_pair(lhs.first + rhs.first,
                         lhs.second + rhs.second);
    return lhs;
}

enum class Direction
{
    Right,
    Left,
    Up,
    Down
};


class BefungeInterpreter
{
public:
    BefungeInterpreter()
    : stack{}
    , grid{{' ','>','>','v'},//add parser
           {'@','v','7','7'},
           {'@','v','7','4'},
           {'^','<','+','<'}}
    , currentPosition{0, 0}
    , currentDirection{Direction::Right}
    {}
    void run()
    {
        while(true)
        {
            displayGrid();
            displayStack();
            interpretCharacterOnCurrentPosition();
            currentPosition += movementMatrix.at(currentDirection);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        };
    }

private:
    using Grid = std::vector<std::vector<char>>;
    using Stack = std::vector<int>;
    const std::map<Direction, Position> movementMatrix{{Direction::Right, Position{0,  1}},
                                                       {Direction::Left,  Position{0, -1}},
                                                       {Direction::Up,    Position{-1, 0}},
                                                       {Direction::Down,  Position{1,  0}}};

    Stack stack;
    Grid grid;
    Position currentPosition;
    Direction currentDirection;

    void interpretCharacterOnCurrentPosition()
    {
        const auto& [x, y] = currentPosition;
        char ch = grid[x][y];
        if(isxdigit(ch)) stack.push_back(ch-'0');
        switch(ch)
        {
            case ' ': /*nop*/ break;
            case '>': changeDirection(Direction::Right); break;
            case '<': changeDirection(Direction::Left);  break;
            case '^': changeDirection(Direction::Up);    break;
            case 'v': changeDirection(Direction::Down);  break;
            case '?': /*tbd*/ break;
            case '#': /*tbd*/ break;
            case '@': exit(EXIT_SUCCESS);

            case '_': /*tbd*/ break;
            case '|': /*tbd*/ break;

            case '+': add(); break;
            case '-': subtract(); break;
            case '*': multiply(); break;
            case '/': divide(); break;
            case '%': modulo(); break;
            case '!': /*tbd*/ break;
            case '`': /*tbd*/ break;
            case ':': /*tbd*/ break;
            case '\\': /*tbd*/ break;
            case '$': /*tbd*/ break;
        }
    }
    void changeDirection(Direction newDirection)
    {
        currentDirection = newDirection;
    }
    auto getTwoLastValuesFromStack()
    {
        auto num1 = stack.back();
        stack.pop_back();
        auto num2 = stack.back();
        stack.pop_back();
        return std::make_pair(num1, num2);
    }
    void add()
    {
        auto [num1, num2] = getTwoLastValuesFromStack();
        stack.push_back(num1 + num2);
    }
    void subtract()
    {
        auto [num1, num2] = getTwoLastValuesFromStack();
        stack.push_back(num1 - num2);
    }
    void multiply()
    {
        auto [num1, num2] = getTwoLastValuesFromStack();
        stack.push_back(num1 * num2);
    }
    void divide()
    {
        auto [num1, num2] = getTwoLastValuesFromStack();
        stack.push_back(num1 / num2);
    }
    void modulo()
    {
        auto [num1, num2] = getTwoLastValuesFromStack();
        stack.push_back(num1 % num2);
    }

    void displayGrid() const
    {
        for(auto i=0; i<grid.size(); ++i)
        {
            for(auto j=0; j<grid[i].size(); ++j)
            {
                std::cout << (std::make_pair(i,j) == currentPosition ? "\033[7m" : "\033[0m")
                          << grid[i][j] << "\033[0m";
            }
            std::cout << std::endl;
        }
    }
    void displayStack() const
    {
        std::cout << "Stack: ";
        for(const auto& el : stack)
            std::cout << el << " ";
        std::cout << std::endl << std::endl;
    }
};
