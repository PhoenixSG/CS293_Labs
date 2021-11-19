#include "SFML/Graphics.hpp"
#include "complex.cpp"
#include "mandelbrot.cpp"
#include "julia.cpp"
#include "dimension_set.h"

//Here we have 4 functions which each deal with moving the graph up, down, left or right.
//We are not recalculating the region which overlaps and only calculating the new region.

//Thus computation is saved, and we get a faster implementation.

//The region to be overlapping can be understood by the way axes are defined in sfml windows.
//The order of iteration requires traversal in different directions for different movement directions
//Thus we require 4 different functions in order to save some processing time

void shift_image_down(int chosen_graph, sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int resolution, float zoom, bool inversion, int julia_max)
{
    //assume down is pressed.
    // This means we recalculate only when i<height-10(say)
    // #pragma omp parallel for
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i < height - 10)
            {
                vertexarray[i * width + j].color = vertexarray[(i + 10) * width + j].color;
            }
            else
            {
                long double x_coor = (coordinate_shift_x + (long double)j) / int(zoom);
                long double y_coor = (coordinate_shift_y + (long double)i) / int(zoom);
                complex_num point;
                point.set_real(x_coor);
                point.set_img(y_coor);
                complex_num z = point;
                int iterations;
                if (chosen_graph == 1)
                {
                    iterations = in_mandelbrot(x_coor, y_coor, resolution);
                    mandelbrot_coloring(i, j, iterations, resolution, vertexarray, inversion);
                }
                else if (chosen_graph == 2)
                {
                    iterations = julia(x_coor, y_coor, julia_max, complex_num(0.285, 0.01));
                    julia_coloring(i, j, iterations, julia_max, vertexarray, inversion);
                }
            }
            // colour this differently
        }
    }
}
void shift_image_up(int chosen_graph, sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int resolution, float zoom, bool inversion, int julia_max)
{
    //assume up is pressed.
    // This means we recalculate only when i>10(say)
    // #pragma omp parallel for
    for (int i = height - 1; i >= 0; i--)
    {
        for (int j = 0; j < width; j++)
        {
            if (i > 10)
            {
                vertexarray[i * width + j].color = vertexarray[(i - 10) * width + j].color;
            }
            else
            {
                long double x_coor = (coordinate_shift_x + (long double)j) / int(zoom);
                long double y_coor = (coordinate_shift_y + (long double)i) / int(zoom);
                complex_num point;
                point.set_real(x_coor);
                point.set_img(y_coor);
                complex_num z = point;
                int iterations;
                if (chosen_graph == 1)
                {
                    iterations = in_mandelbrot(x_coor, y_coor, resolution);
                    mandelbrot_coloring(i, j, iterations, resolution, vertexarray, inversion);
                }
                else if (chosen_graph == 2)
                {
                    iterations = julia(x_coor, y_coor, julia_max, complex_num(0.285, 0.01));
                    julia_coloring(i, j, iterations, julia_max, vertexarray, inversion);
                }
            }
            // colour this differently
        }
    }
}
void shift_image_left(int chosen_graph, sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int resolution, float zoom, bool inversion, int julia_max)
{
    //assume left is pressed.
    // This means we recalculate only when j<10(say)
#pragma omp parallel for
    for (int i = 0; i < height; i++)
    {
        for (int j = width - 1; j >= 0; j--)
        {
            if (j > 10)
            {
                vertexarray[i * width + j].color = vertexarray[i * width + j - 10].color;
            }
            else
            {
                long double x_coor = (coordinate_shift_x + (long double)j) / int(zoom);
                long double y_coor = (coordinate_shift_y + (long double)i) / int(zoom);
                complex_num point;
                point.set_real(x_coor);
                point.set_img(y_coor);
                complex_num z = point;
                int iterations;
                if (chosen_graph == 1)
                {
                    iterations = in_mandelbrot(x_coor, y_coor, resolution);
                    mandelbrot_coloring(i, j, iterations, resolution, vertexarray, inversion);
                }
                else if (chosen_graph == 2)
                {
                    iterations = julia(x_coor, y_coor, julia_max, complex_num(0.285, 0.01));
                    julia_coloring(i, j, iterations, julia_max, vertexarray, inversion);
                }
            }
            // colour this differently
        }
    }
}
void shift_image_right(int chosen_graph, sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int resolution, float zoom, bool inversion, int julia_max)
{
    //assume right is pressed.
    // This means we recalculate only when j>width-10(say)
#pragma omp parallel for
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j < width - 10)
            {
                vertexarray[i * width + j].color = vertexarray[i * width + j + 10].color;
            }
            else
            {
                long double x_coor = (coordinate_shift_x + (long double)j) / int(zoom);
                long double y_coor = (coordinate_shift_y + (long double)i) / int(zoom);
                complex_num point;
                point.set_real(x_coor);
                point.set_img(y_coor);
                complex_num z = point;
                int iterations;
                if (chosen_graph == 1)
                {
                    iterations = in_mandelbrot(x_coor, y_coor, resolution);
                    mandelbrot_coloring(i, j, iterations, resolution, vertexarray, inversion);
                }
                else if (chosen_graph == 2)
                {
                    iterations = julia(x_coor, y_coor, julia_max, complex_num(0.285, 0.01));
                    julia_coloring(i, j, iterations,  julia_max, vertexarray, inversion);
                }
            }
            // colour this differently
        }
    }
}