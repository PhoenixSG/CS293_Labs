#include <math.h>

void julia_coloring(int i, int j, int iterations, int total, sf::VertexArray &vertexarray)
{
    //color pixel based on the number of iterations
    int width = 1280;

    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
    float fraction = std::min(255.0f, iterations * 255.0f / total);
    if (fraction < 30)
    {
        sf::Color color(8 * fraction, 0, 0);
        vertexarray[i * width + j].color = color;
    }
    else if (fraction < 60)
    {
        sf::Color color(4 * fraction, 0, 4 * fraction);
        vertexarray[i * width + j].color = color;
    }
    else if (fraction < 120)
    {
        sf::Color color(0, 2 * fraction, 2 * fraction);
        vertexarray[i * width + j].color = color;
    }
    else if (fraction < 180)
    {
        sf::Color color(3 * fraction / 2, 3 * fraction / 2, 0);
        vertexarray[i * width + j].color = color;
    }
    else
    {
        sf::Color color(0, fraction, 0);
        vertexarray[i * width + j].color = color;
    }
}