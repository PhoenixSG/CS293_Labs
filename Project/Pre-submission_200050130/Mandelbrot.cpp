#include "SFML/Graphics.hpp"
#include <bits/stdc++.h>

using namespace std;
const int width = 1280;
const int height = 720;

//used for complex numbers
class complex_num
{
    private:
        long double real_part;
        long double imaginary_part;
    public:
        long double get_real(){
            return real_part;
        }
        long double get_img(){
            return imaginary_part;
        }
        void set_real(long double real){
            real_part = real;
        }
        void set_img(long double img){
            imaginary_part = img;
        }
        long double get_magnitude(){
            return sqrt(real_part*real_part+imaginary_part*imaginary_part);
        }
        long double get_angle(){
            return atan(imaginary_part/real_part);
        }
        complex_num operator * (complex_num object){
            complex_num product;
            product.set_real(real_part*object.get_real()-imaginary_part*object.get_img());
            product.set_img(real_part*object.get_img()+imaginary_part*object.get_real());
            return product;
        }
        complex_num operator + (complex_num object){
            complex_num sum;
            sum.set_real(real_part+object.get_real());
            sum.set_img(imaginary_part+object.get_img());
            return sum;
        }

};

void generate_graph(sf::VertexArray &vertexarray, int x_shift, int y_shift, int precision_needed, float zoom)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            long double x_coor = ((long double)j + x_shift) / int(zoom);
            long double y_coor = ((long double)i + y_shift) / int(zoom);
            complex_num point;
            point.set_real(x_coor);
            point.set_img(y_coor);
            complex_num z = point;
            int iterations = 0;
            for (int k = 0; k < precision_needed; k++)
            {
                complex_num z_new;
                z_new = z*z;
                z_new = z_new+point;
                z = z_new;
                iterations++;
                if (z.get_magnitude() > 3)
                    break;
            }
            //color pixel based on the number of iterations
            vertexarray[i * width + j].position = sf::Vector2f(j, i);
            sf::Color color(iterations * 255.0f / precision_needed, iterations * 255.0f / precision_needed, iterations * 255.0f / precision_needed);
            vertexarray[i * width + j].color = color;
            // colour this differently
        }
    }
    cout<<"ZOOM is "<<zoom<<" and precision level is "<<precision_needed<<endl;
}

int main()
{
    cout<<"Right click, Left click or scroll. Works slower with scroll"<<endl;
    sf::String heading = "Mandelbrot Set Plotter";
    sf::RenderWindow window(sf::VideoMode(width, height), heading);
    window.setFramerateLimit(30);
    sf::VertexArray pointmap(sf::Points, width * height);

    float zoom = 256.0f;
    int precision = 100;
    int x_shift = -width / 2;
    int y_shift = -height / 2;

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
//learn what is pragma better
                    for (int i = 0; i < width * height; i++)
                    {
                        pointmap[i].color = sf::Color::Black;
                    }
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