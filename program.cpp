#include <iostream>
#include <unistd.h>
#include <termios.h>

using namespace std;

typedef unsigned int size;

#include "Renderer/renderer.hpp"
#include "Table/table.hpp"
#include "Snake/snake.hpp"

struct termios orig_termios;

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void getInput(char *c, direction l_dir)
{
    char _c;

    while (read(STDIN_FILENO, &_c, 1))
    {
        if ((_c == 'w' && l_dir != direction::up) ||
            (_c == 'd' && l_dir != direction::right) ||
            (_c == 's' && l_dir != direction::down) ||
            (_c == 'a' && l_dir != direction::left))
        {
            *c = _c;
            return;
        }
    }

    *c = 0;
}

int main()
{
    enableRawMode();

    Table table(20, 10);
    Snake snake(3, 3, 5);

    srand(time(NULL));
    pos fruit = {.x = 15, .y = 5};

    table.setCursorVisible(false);
    table.setFooter("Score: 0");

    table.display();

    direction dir = direction::right;
    point *pps;

    char input;
    double delay = 1e7, timer = delay;

    int score = 0;
    char str_score[13];
    while (input != 3)
    {
        if (timer <= delay)
        {
            timer += 0.1;
            continue;
        }

        getInput(&input, dir);

        if (input == 'w' && dir != direction::down)
        {
            dir = direction::up;
        }
        else if (input == 'd' && dir != direction::left)
        {
            dir = direction::right;
        }
        else if (input == 's' && dir != direction::up)
        {
            dir = direction::down;
        }
        else if (input == 'a' && dir != direction::right)
        {
            dir = direction::left;
        }

        snake.move(dir);

        pos snake_head = snake.head();
        if (snake_head.x == fruit.x && snake_head.y == fruit.y)
        {
            snake.grow();

            do
            {
                fruit = {.x = (size)rand() % 20,
                         .y = (size)rand() % 10 };
            } while (snake.isInSnake(fruit));

            delay -= 1e5;

            score++;
            sprintf(str_score, "Score: %d", score);

            table.setFooter(str_score);
        }

        if (snake.isDead())
        {
            break;
        }

        pps = snake.returnPoints('*');
        if (!table.draw('#', fruit.x, fruit.y) || !table.draw('_', snake.last_back.x, snake.last_back.y) || !table.multipleDraw(pps, snake.length))
        {
            break;
        }
        free(pps);

        table.display();

        timer = 0;
    }

    table.setCursorVisible(true);

    disableRawMode();

    return 0;
}
