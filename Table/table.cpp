Table::Table(size width, size height) : Renderer(width, height)
{
    for (size y = 0; y < this->height; y++)
    {
        for (size x = 0; x < this->width; x++)
        {
            this->drawAt('_', x, y);
        }
    }

    cout << "\e[0J" << '\n' << '\n';
}

bool Table::draw(char ch, size x, size y)
{
    return this->drawAt(ch, x, y);
}

bool Table::multipleDraw(const point *chs, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        if (!this->drawAt(chs[i].ch, chs[i].x, chs[i].y))
        {
            return false;
        }
    }

    return true;
}

void Table::setBorder(char border)
{
    for (size x = 0; x < this->width; x++)
    {
        this->drawAt(border, x, 0);
        this->drawAt(border, x, this->height - 1);
    }

    for (size y = 1; y < this->height - 1; y++)
    {
        this->drawAt(border, 0, y);
        this->drawAt(border, this->width - 1, y);
    }
}

void Table::display()
{
    if (this->using_footer) {
        cout << "\e[1A";
        cout << this->footer << '\n';
    }

    this->render();
}

void Table::setCursorVisible(bool vis = false)
{
    if (vis)
    {
        cout << "\e[?25h";
    }
    else
    {
        cout << "\e[?25l";
    }
}

void Table::setFooter(const char *footer) {
    this->using_footer = true;
    this->footer = footer;
}
