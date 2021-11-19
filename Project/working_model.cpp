#include "SFML/Graphics.hpp"
#include <bits/stdc++.h>

using namespace std;
//resolution of the window
const int width = 1280;
const int height = 720;

//used for complex numbers
class complex_num
{
private:
    long double real_part;
    long double imaginary_part;

public:

    complex_num(long double real, long double imaginary){
        real_part = real;
        imaginary_part = imaginary;
    }
    complex_num(){
        real_part = 0;
        imaginary_part = 0;
    }
    long double get_real()
    {
        return real_part;
    }
    long double get_img()
    {
        return imaginary_part;
    }
    void set_real(long double real)
    {
        real_part = real;
    }
    void set_img(long double img)
    {
        imaginary_part = img;
    }
    long double get_magnitude()
    {
        return sqrt(real_part * real_part + imaginary_part * imaginary_part);
    }
    long double get_angle()
    {
        return atan(imaginary_part / real_part);
    }
    complex_num operator*(complex_num object)
    {
        complex_num product;
        product.set_real(real_part * object.get_real() - imaginary_part * object.get_img());
        product.set_img(real_part * object.get_img() + imaginary_part * object.get_real());
        return product;
    }
    complex_num operator+(complex_num object)
    {
        complex_num sum;
        sum.set_real(real_part + object.get_real());
        sum.set_img(imaginary_part + object.get_img());
        return sum;
    }

    // over load addition
    // simple tasks
};
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
                int iterations = 0; //keep track of the number of iterations
                for (int k = 0; k < precision; k++)
                {
                    complex_num z_new;
                    z_new = z * z;
                    z_new = z_new + point;
                    z = z_new;
                    iterations++;
                    if (z.get_magnitude() > 3)
                        break;
                }
                //color pixel based on the number of iterations
                if (iterations < precision / 4.0f)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(iterations * 255.0f / (precision / 4.0f), 0, 0);
                    vertexarray[i * width + j].color = color;
                }
                else if (iterations < precision / 2.0f)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, iterations * 255.0f / (precision / 2.0f), 0);
                    vertexarray[i * width + j].color = color;
                }
                else if (iterations < precision)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, 0, iterations * 255.0f / precision);
                    vertexarray[i * width + j].color = color;
                }
                else
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(150, 150, 150);
                    vertexarray[i * width + j].color = color;
                }
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
                int iterations = 0; //keep track of the number of iterations
                for (int k = 0; k < precision; k++)
                {
                    complex_num z_new;
                    z_new = z * z;
                    z_new = z_new + point;
                    z = z_new;
                    iterations++;
                    if (z.get_magnitude() > 3)
                        break;
                }
                //color pixel based on the number of iterations
                if (iterations < precision / 4.0f)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(iterations * 255.0f / (precision / 4.0f), 0, 0);
                    vertexarray[i * width + j].color = color;
                }
                else if (iterations < precision / 2.0f)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, iterations * 255.0f / (precision / 2.0f), 0);
                    vertexarray[i * width + j].color = color;
                }
                else if (iterations < precision)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, 0, iterations * 255.0f / precision);
                    vertexarray[i * width + j].color = color;
                }
                else
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(150, 150, 150);
                    vertexarray[i * width + j].color = color;
                }
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
                int iterations = 0; //keep track of the number of iterations
                for (int k = 0; k < precision; k++)
                {
                    complex_num z_new;
                    z_new = z * z;
                    z_new = z_new + point;
                    z = z_new;
                    iterations++;
                    if (z.get_magnitude() > 3)
                        break;
                }
                //color pixel based on the number of iterations
                if (iterations < precision / 4.0f)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(iterations * 255.0f / (precision / 4.0f), 0, 0);
                    vertexarray[i * width + j].color = color;
                }
                else if (iterations < precision / 2.0f)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, iterations * 255.0f / (precision / 2.0f), 0);
                    vertexarray[i * width + j].color = color;
                }
                else if (iterations < precision)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, 0, iterations * 255.0f / precision);
                    vertexarray[i * width + j].color = color;
                }
                else
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(150, 150, 150);
                    vertexarray[i * width + j].color = color;
                }
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
                int iterations = 0; //keep track of the number of iterations
                for (int k = 0; k < precision; k++)
                {
                    complex_num z_new;
                    z_new = z * z;
                    z_new = z_new + point;
                    z = z_new;
                    iterations++;
                    if (z.get_magnitude() > 3)
                        break;
                }
                //color pixel based on the number of iterations
                if (iterations < precision / 4.0f)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(iterations * 255.0f / (precision / 4.0f), 0, 0);
                    vertexarray[i * width + j].color = color;
                }
                else if (iterations < precision / 2.0f)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, iterations * 255.0f / (precision / 2.0f), 0);
                    vertexarray[i * width + j].color = color;
                }
                else if (iterations < precision)
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, 0, iterations * 255.0f / precision);
                    vertexarray[i * width + j].color = color;
                }
                else
                {
                    // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                    sf::Color color(150, 150, 150);
                    vertexarray[i * width + j].color = color;
                }
            }
            // colour this differently
        }
    }
}

void generate_graph(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int precision, float zoom)
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
            int iterations = 0; //keep track of the number of iterations
            for (int k = 0; k < precision; k++)
            {
                complex_num z_new;
                z_new = z * z;
                z_new = z_new + point;
                z = z_new;
                iterations++;
                if (z.get_magnitude() > 3)
                    break;
            }
            //color pixel based on the number of iterations
            if (iterations < precision / 4.0f)
            {
                // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                sf::Color color(iterations * 255.0f / (precision / 4.0f), 0, 0);
                vertexarray[i * width + j].color = color;
            }
            else if (iterations < precision / 2.0f)
            {
                // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                sf::Color color(0, iterations * 255.0f / (precision / 2.0f), 0);
                vertexarray[i * width + j].color = color;
            }
            else if (iterations < precision)
            {
                // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                sf::Color color(0, 0, iterations * 255.0f / precision);
                vertexarray[i * width + j].color = color;
            }
            else
            {
                // vertexarray[i * width + j].position = sf::Vector2f(j, i);
                sf::Color color(150, 150, 150);
                vertexarray[i * width + j].color = color;
            }
            // colour this differently
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

    generate_graph(pointmap, x_shift, y_shift, precision, zoom);

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
                generate_graph(pointmap, x_shift, y_shift, precision, zoom);
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
                    generate_graph(pointmap, x_shift, y_shift, precision, zoom);
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
                    generate_graph(pointmap, x_shift, y_shift, precision, zoom);
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
                    int random_number = 10.0*rand()/RAND_MAX+1;
                    cout<<random_number<<endl;
                    zoom = min(pow(10, 9),256.0f*pow(2, random_number));
                    precision = min(4000, 100+200*random_number);
                    // x_shift = ((rand()%2)*2-1)*rand();
                    // y_shift = ((rand()%2)*2-1)*rand();
                    generate_graph(pointmap, x_shift, y_shift, precision, zoom);
                }
                if (event.key.code == sf::Keyboard::H)
                {
                    zoom = 256.0f;
                    precision = 100;
                    x_shift = -width / 2;
                    y_shift = -height / 2;
                    generate_graph(pointmap, x_shift, y_shift, precision, zoom);
                }
            }
        }

        window.clear();
        window.draw(pointmap);
        window.display();
    }

    return 0;
}