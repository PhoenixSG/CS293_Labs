#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#define MAX_ITERATION 255

double isMandelbrot(double x, double y)
{
    int w = 1000;
    int h = 800;

    double x, y;
    double range_x = 4, range_y = 4;

    for (int i = 0; i <= h; i += 1)
    {
        for (int j = 0; j <= w; j += 1)
        {

            x = 2.0 * j / w * range_x - range_x;
            y = 2.0 * i / h * range_y - range_y;
            // cout<<x<<" "<<y<<endl;
            double x_1 = x, y_1 = y;
            int l;
            for (l = 0; l < 100; l++)
            {
                int real = x * x - y * y;
                int imag = 2 * x * y;

                x = real + x_1;
                y = imag + y_1;

                if (x * x + y * y > 10)
                {
                    break;
                }
            }

            if (l <100)
            { //not in mandelbrot
                
            }
            else
            { //in mandelbrot set
                
            }

            return check;
        }
    }
}

int main()
{
    // sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    sf::RenderWindow window(sf::VideoMode(200, 200), "WORKS!", sf::Style::Close | sf::Style::Resize);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type = event.Closed)
            {
                window.close();
            }
        }
    }

    return 0;
}