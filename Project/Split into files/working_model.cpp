#include "SFML/Graphics.hpp"
#include <bits/stdc++.h>
#include "complex.cpp"
#include "mandelbrot.cpp"
#include "julia.cpp"
// #include "textbox.cpp"

using namespace std;
//resolution of the window
const int width = 1280;
const int height = 720;

void shift_image_down(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int precision, float zoom)
{
    //assume right is pressed.
    // This means we recalculate only when j>width-10(say)
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
                int iterations = in_mandelbrot(x_coor, y_coor, precision);
                mandelbrot_coloring(i, j, iterations, precision, vertexarray);

                // int iterations = julia(x_coor, y_coor, precision, complex_num(0.285, 0.01));
                // julia_coloring(i, j, iterations, precision, vertexarray);
            }
            // colour this differently
        }
    }
}
void shift_image_up(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int precision, float zoom)
{
    //assume right is pressed.
    // This means we recalculate only when j>width-10(say)
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
                int iterations = in_mandelbrot(x_coor, y_coor, precision);
                mandelbrot_coloring(i, j, iterations, precision, vertexarray);

                // int iterations = julia(x_coor, y_coor, precision, complex_num(0.285, 0.01));
            }
            // colour this differently
        }
    }
}
void shift_image_left(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int precision, float zoom)
{
    //assume right is pressed.
    // This means we recalculate only when j>width-10(say)
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
                int iterations = in_mandelbrot(x_coor, y_coor, precision);
                mandelbrot_coloring(i, j, iterations, precision, vertexarray);

                // int iterations = julia(x_coor, y_coor, precision, complex_num(0.285, 0.01));
            }
            // colour this differently
        }
    }
}
void shift_image_right(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int precision, float zoom)
{
    //assume right is pressed.
    // This means we recalculate only when j>width-10(say)
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
                int iterations = in_mandelbrot(x_coor, y_coor, precision);
                mandelbrot_coloring(i, j, iterations, precision, vertexarray);

                // int iterations = julia(x_coor, y_coor, precision, complex_num(0.285, 0.01));
            }
            // colour this differently
        }
    }
}

void generate_mandelhbrot_set(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int precision, float zoom)
{
#pragma omp parallel for
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            long double x_coor = (coordinate_shift_x + (long double)j) / int(zoom);
            long double y_coor = (coordinate_shift_y + (long double)i) / int(zoom);
            complex_num point;
            point.set_real(x_coor);
            point.set_img(y_coor);
            complex_num z = point;
            int iterations = in_mandelbrot(x_coor, y_coor, precision);
            mandelbrot_coloring(i, j, iterations, precision, vertexarray);
        }
    }
    cout << "ZOOM is " << zoom << " and precision level is " << precision << endl;
    cout << "xshift is " << coordinate_shift_x << " and yshift is " << coordinate_shift_y << endl;
}

void generate_mandelbrot_set(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int precision, float zoom)
{
    int iterations[height][width];
    int maximum = 0;
#pragma omp parallel for
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            long double x_coor = (coordinate_shift_x + (long double)j) / int(zoom);
            long double y_coor = (coordinate_shift_y + (long double)i) / int(zoom);
            complex_num point;
            point.set_real(x_coor);
            point.set_img(y_coor);
            complex_num z = point;
            iterations[i][j] = julia(x_coor, y_coor, precision, complex_num(0.285, 0.01));
            maximum = max(iterations[i][j], maximum);
            
        }
    }
    cout<<maximum<<endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            julia_coloring(i, j, iterations[i][j], maximum, vertexarray);
        }
    }

    cout << "ZOOM is " << zoom << " and precision level is " << precision << endl;
    cout << "xshift is " << coordinate_shift_x << " and yshift is " << coordinate_shift_y << endl;
}

int main()
{
    sf::String heading = "Mandelbrot Set Plotter";
    sf::RenderWindow window(sf::VideoMode(width, height), heading);
    window.setFramerateLimit(30);
    sf::VertexArray pointmap(sf::Points, width * height);

    float zoom = 256.0f;
    int precision = 100;
    int x_shift = -width / 2;
    int y_shift = -height / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pointmap[i * width + j].position = sf::Vector2f(j, i);
        }
    }

    generate_mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelMoved)
            {
                double zoom_factor = 1.25;
                if (event.mouseWheel.delta == 1)
                {
                    x_shift += (event.mouseWheel.x + x_shift) * (zoom_factor - 1);
                    y_shift += (event.mouseWheel.y + y_shift) * (zoom_factor - 1);
                    zoom *= zoom_factor;
                    precision = min(4000.0, precision + 200 * (zoom_factor - 1));
                }
                else if (event.mouseWheel.delta == -1)
                {
                    x_shift /= zoom_factor;
                    y_shift /= zoom_factor;
                    x_shift -= event.mouseWheel.x * (zoom_factor - 1) / zoom_factor;
                    y_shift -= event.mouseWheel.y * (zoom_factor - 1) / zoom_factor;
                    zoom /= zoom_factor;
                    precision = max(100.0, precision - 200 * (zoom_factor - 1));
                }
#pragma omp parallel for
                for (int i = 0; i < width * height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }
                generate_mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                double zoom_factor = 2;
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    x_shift += (event.mouseWheel.x + x_shift) * (zoom_factor - 1);
                    y_shift += (event.mouseWheel.y + y_shift) * (zoom_factor - 1);
                    zoom *= zoom_factor;
                    precision = min(4000.0, precision + 200 * (zoom_factor - 1));
#pragma omp parallel for
                    for (int i = 0; i < width * height; i++)
                    {
                        pointmap[i].color = sf::Color::Black;
                    }
                    generate_mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom);
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    x_shift /= zoom_factor;
                    y_shift /= zoom_factor;
                    x_shift -= event.mouseWheel.x * (zoom_factor - 1) / zoom_factor;
                    y_shift -= event.mouseWheel.y * (zoom_factor - 1) / zoom_factor;
                    zoom /= zoom_factor;
                    precision = max(100.0, precision - 200 * (zoom_factor - 1));
//learn what is pragma
#pragma omp parallel for
                    for (int i = 0; i < width * height; i++)
                    {
                        pointmap[i].color = sf::Color::Black;
                    }
                    generate_mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom);
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    y_shift -= 10;
                    shift_image_up(pointmap, x_shift, y_shift, precision, zoom);
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    y_shift += 10;
                    shift_image_down(pointmap, x_shift, y_shift, precision, zoom);
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    x_shift -= 10;
                    shift_image_left(pointmap, x_shift, y_shift, precision, zoom);
                }
                if (event.key.code == sf::Keyboard::Right)
                {

                    x_shift += 10;
                    shift_image_right(pointmap, x_shift, y_shift, precision, zoom);
                }
                if (event.key.code == sf::Keyboard::R)
                {
                    int random_number = 10.0 * rand() / RAND_MAX + 1;
                    cout << random_number << endl;
                    zoom = min(pow(10, 9), 256.0f * pow(2, random_number));
                    precision = min(4000, 100 + 200 * random_number);
                    // x_shift = ((rand()%2)*2-1)*rand();
                    // y_shift = ((rand()%2)*2-1)*rand();
                    generate_mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom);
                }
                if (event.key.code == sf::Keyboard::H)
                {
                    zoom = 256.0f;
                    precision = 100;
                    x_shift = -width / 2;
                    y_shift = -height / 2;
                    generate_mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom);
                }
            }
        }

        window.clear();
        window.draw(pointmap);
        window.display();
    }

    return 0;
}