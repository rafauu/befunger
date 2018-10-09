#pragma once

struct Position
{
    Position(int x = 0,
             int y = 0)
    : x{x}
    , y{y}
    {}

    bool operator==(const Position& rhs) const
    {
        return this->x == rhs.x and
               this->y == rhs.y;
    }

    Position& operator+=(const Position& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

    int x;
    int y;
};

