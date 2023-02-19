struct point
{
    size x;
    size y;
    char ch;
};

class Table : private Renderer
{
private:
    const char *footer;
    bool using_footer = false;

public:
    Table(size width, size height);
    void setBorder(char border);
    bool multipleDraw(const point *chs, size_t length);
    bool draw(char ch, size x, size y);
    void display();
    void setCursorVisible(bool vis);
    void setFooter(const char *footer);
};

#include "table.cpp"
