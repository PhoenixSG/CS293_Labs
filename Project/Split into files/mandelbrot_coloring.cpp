#include "SFML/Graphics.hpp"
#include "dimension_set.h"

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

void mandelbrot_coloring(int i, int j, int iterations, int total, sf::VertexArray &vertexarray, bool inversion)
{
    //color pixel based on the number of iterations
    int width = 1280;

    if (iterations < total / 6.0f)
    {
        vertexarray[i * width + j].position = sf::Vector2f(j, i);
        sf::Color color(iterations * 255.0f / (total / 6.0f), 0, 0);
        vertexarray[i * width + j].color = color;
    }
    else if (iterations < 2 * total / 6.0f)
    {
        vertexarray[i * width + j].position = sf::Vector2f(j, i);
        sf::Color color(iterations * 255.0f / (total / 3.0f), 0, iterations * 255.0f / (total / 3.0f));

        vertexarray[i * width + j].color = color;
    }
    else if (iterations < total / 2.0f)
    {
        vertexarray[i * width + j].position = sf::Vector2f(j, i);
        sf::Color color(0, 0, iterations * 255.0f / (total / 2.0f));
        vertexarray[i * width + j].color = color;
    }
    else if (iterations < 4 * total / 6.0f)
    {
        vertexarray[i * width + j].position = sf::Vector2f(j, i);
        sf::Color color(0, iterations * 255.0f / (4 * total / 6.0f), iterations * 255.0f / (4 * total / 6.0f));
        vertexarray[i * width + j].color = color;
    }
    else if (iterations < 5 * total / 6.0f)
    {
        vertexarray[i * width + j].position = sf::Vector2f(j, i);
        sf::Color color(0, iterations * 255.0f / (5 * total / 6.0f), 0);

        vertexarray[i * width + j].color = color;
    }
    else if (iterations < total)
    {
        vertexarray[i * width + j].position = sf::Vector2f(j, i);
        sf::Color color(iterations * 255.0f / (total), iterations * 255.0f / (total), 0);
        vertexarray[i * width + j].color = color;
    }
    else
    {
        vertexarray[i * width + j].position = sf::Vector2f(j, i);
        sf::Color color(255, 255, 255);
        vertexarray[i * width + j].color = color;
    }
    if (inversion)
    {
        sf::Color color(255 - vertexarray[i * width + j].color.r, 255 - vertexarray[i * width + j].color.g, 255 - vertexarray[i * width + j].color.b);
        vertexarray[i * width + j].color = color;
    }
}
