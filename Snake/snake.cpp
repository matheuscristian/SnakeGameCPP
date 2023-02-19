Snake::Snake(size_t length, size x, size y)
{
    if (length <= 0)
    {
        throw invalid_argument("Received 0 or negative value");
    }

    this->body = (pos *)malloc(sizeof(pos) * length);

    size t_x = x;
    for (size_t i = 0; i < length; i++)
    {
        this->body[i] = {.x = t_x, .y = y};
        t_x++;
    }

    this->length = length;
    this->last_back = {.x = 0, .y = 0};
}

Snake::~Snake()
{
    free(this->body);
}

void Snake::move(direction dir)
{
    this->last_back = this->body[0];

    for (size_t i = 0; i < this->length - 1; i++)
    {
        this->body[i] = this->body[i + 1];
    }

    switch (dir)
    {
    case direction::up:
        this->body[this->length - 1].y--;
        break;
    case direction::right:
        this->body[this->length - 1].x++;
        break;
    case direction::down:
        this->body[this->length - 1].y++;
        break;
    case direction::left:
        this->body[this->length - 1].x--;
        break;
    default:
        break;
    }
}

void Snake::grow()
{
    pos temp_body[this->length + 1];

    for (size_t i = 0; i < this->length; i++)
    {
        temp_body[i + 1] = {.x = this->body[i].x, .y = this->body[i].y};
    }

    temp_body[0] = {.x = this->body[0].x, .y = this->body[0].y};

    this->length++;
    this->body = (pos *)realloc(this->body, sizeof(pos) * this->length);

    for (size_t i = 0; i < this->length; i++)
    {
        this->body[i] = {.x = temp_body[i].x, .y = temp_body[i].y};
    }
}

point *Snake::returnPoints(char ch)
{
    point *points = (point *)malloc(sizeof(point) * this->length);

    for (size_t i = 0; i < this->length; i++)
    {
        points[i] = {.x = this->body[i].x, .y = this->body[i].y, .ch = ch};
    }

    return points;
}

bool Snake::isDead()
{
    for (size_t i = 0; i < this->length - 1; i++)
    {
        if (this->body[i].x == this->body[this->length - 1].x &&
            this->body[i].y == this->body[this->length - 1].y)
        {
            return true;
        }
    }

    return false;
}

pos Snake::head()
{
    return this->body[this->length - 1];
}

bool Snake::isInSnake(pos item)
{
    for (size_t i = 0; i < this->length; i++)
    {
        if (this->body[i].x == item.x &&
            this->body[i].y == item.y)
        {
            return true;
        }
    }

    return false;
}
