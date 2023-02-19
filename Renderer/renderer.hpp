class Renderer
{
private:
    char **matrix;

protected:
    size width;
    size height;

public:
    Renderer(size width, size height);
    ~Renderer();
    bool drawAt(char ch, size x, size y);
    void render();
};

#include "renderer.cpp"
