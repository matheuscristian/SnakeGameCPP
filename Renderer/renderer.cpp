Renderer::Renderer(size width, size height)
{
    if (width <= 0 || height <= 0)
    {
        throw invalid_argument("Received 0 or negative value");
    }

    this->matrix = (char **)malloc(sizeof(char *) * height);
    if (!this->matrix)
    {
        throw runtime_error("Memory allocation failed");
    }

    for (size i = 0; i < height; i++)
    {
        this->matrix[i] = (char *)malloc(sizeof(char) * width);
        if (!this->matrix[i])
        {
            throw runtime_error("Memory allocation failed");
        }
    }

    this->width = width;
    this->height = height;
}

Renderer::~Renderer()
{
    for (size i = 0; i < height; i++)
    {
        free(this->matrix[i]);
    }

    free(this->matrix);
}

bool Renderer::drawAt(char ch, size x, size y)
{
    if ((x < 0 || x >= this->width) || (y < 0 || y >= this->height))
    {
        return false;
    }

    this->matrix[y][x] = ch;

    return (this->matrix[y][x] == ch);
}

void Renderer::render()
{
    for (size y = 0; y < this->height; y++)
    {
        for (size x = 0; x < this->width; x++)
        {
            cout << this->matrix[y][x];
        }
        cout << '\n';
    }
    cout << "\e[" << height << "A";
}
