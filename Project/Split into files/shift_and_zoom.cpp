#include "SFML/Graphics.hpp"
#include "complex.cpp"
#include "mandelbrot.cpp"
#include "dimension_set.h"

void shift_image_down(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int resolution, float zoom, bool inversion)
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
                int iterations = in_mandelbrot(x_coor, y_coor, resolution);
                mandelbrot_coloring(i, j, iterations, resolution, vertexarray, inversion);

                // int iterations = julia(x_coor, y_coor, resolution, complex_num(0.285, 0.01));
                // julia_coloring(i, j, iterations, resolution, vertexarray);
            }
            // colour this differently
        }
    }
}
void shift_image_up(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int resolution, float zoom, bool inversion)
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
                int iterations = in_mandelbrot(x_coor, y_coor, resolution);
                mandelbrot_coloring(i, j, iterations, resolution, vertexarray, inversion);

                // int iterations = julia(x_coor, y_coor, resolution, complex_num(0.285, 0.01));
            }
            // colour this differently
        }
    }
}
void shift_image_left(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int resolution, float zoom, bool inversion)
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
                int iterations = in_mandelbrot(x_coor, y_coor, resolution);
                mandelbrot_coloring(i, j, iterations, resolution, vertexarray, inversion);

                // int iterations = julia(x_coor, y_coor, resolution, complex_num(0.285, 0.01));
            }
            // colour this differently
        }
    }
}
void shift_image_right(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int resolution, float zoom, bool inversion)
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
                int iterations = in_mandelbrot(x_coor, y_coor, resolution);
                mandelbrot_coloring(i, j, iterations, resolution, vertexarray, inversion);

                // int iterations = julia(x_coor, y_coor, resolution, complex_num(0.285, 0.01));
            }
            // colour this differently
        }
    }
}