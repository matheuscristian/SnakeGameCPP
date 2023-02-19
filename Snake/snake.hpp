struct pos
{
    size x;
    size y;
};

enum direction
{
    up,
    right,
    down,
    left
};

class Snake
{
private:
    pos *body;

public:
    size_t length;
    pos last_back;
    Snake(size_t length, size x, size y);
    ~Snake();
    void move(direction dir);
    void grow();
    bool isDead();
    bool isInSnake(pos item);
    pos head();
    point *returnPoints(char ch);
};

#include "snake.cpp"
