#include <math.h>

// Colour based on the number of iterations.

#ifndef INVERSIONS
#define INVERSIONS

void invert_colours(sf::VertexArray &vertexarray)
{
#pragma omp parallel for
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sf::Color color(255 - vertexarray[i * width + j].color.r, 255 - vertexarray[i * width + j].color.g, 255 - vertexarray[i * width + j].color.b);
            vertexarray[i * width + j].color = color;
        }
    }
}
#endif

void julia_coloring(int i, int j, int iterations, int total, sf::VertexArray &vertexarray, bool inversion)
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
    if (inversion)
    {
        sf::Color color(255 - vertexarray[i * width + j].color.r, 255 - vertexarray[i * width + j].color.g, 255 - vertexarray[i * width + j].color.b);
        vertexarray[i * width + j].color = color;
    }
}