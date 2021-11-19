#include "SFML/Graphics.hpp"
#include <bits/stdc++.h>
#include "complex.cpp"
#include "mandelbrot.cpp"
#include "julia.cpp"
#include "shift_and_zoom.cpp"
#include "dimension_set.h"
#include "double_stack_model.cpp"
#include "button.cpp"

using namespace std;
//resolution of the window

int chosen_graph = 1;
bool inversion = false;

void generate_graph(sf::VertexArray &vertexarray, int coordinate_shift_x, int coordinate_shift_y, int resolution, float zoom)
{
    if (chosen_graph == 1)
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
                int iterations = in_mandelbrot(x_coor, y_coor, resolution);
                mandelbrot_coloring(i, j, iterations, resolution, vertexarray, inversion);
            }
        }
        cout << "ZOOM is " << zoom << " and resolution level is " << resolution << endl;
        // cout << "xshift is " << coordinate_shift_x << " and yshift is " << coordinate_shift_y << endl;
    }
    else if (chosen_graph == 2)
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
                iterations[i][j] = julia(x_coor, y_coor, resolution, complex_num(0.285, 0.01));
                maximum = max(iterations[i][j], maximum);
            }
        }
        // cout << maximum << endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                julia_coloring(i, j, iterations[i][j], maximum, vertexarray);
            }
        }

        cout << "ZOOM- " << zoom << " Resolution- " << resolution << endl;
        // cout << "xshift is " << coordinate_shift_x << " and yshift is " << coordinate_shift_y << endl;
    }
}

int main()
{
    cout << "Hello and Welcome to my Mandelbort Set Project.\n";
    cout << "Please read the Instructions in the README file before proceeding.\n";
    cout << "Here you find and interactive graph which you can use to study various properties of different graphs\n";
    cout << "Please choose the graph you like!\n\n";

    sf::String heading = "Mandelbrot Set Plotter";
    sf::RenderWindow window(sf::VideoMode(width, height), heading);
    window.setFramerateLimit(100);

    sf::VertexArray pointmap(sf::Points, width * height);
    sf::Texture texture;

    sf::Font TNR;
    TNR.loadFromFile("timesnewroman.ttf");

    float width_box = 300;
    float height_box = 100;

    Button mandelButton("MANDELBROT", {width_box, height_box}, 20, sf::Color::Black, sf::Color::Green);
    mandelButton.set_Font(TNR);
    mandelButton.set_Position({width / 4 - width_box / 2, height / 2 - height_box / 2});

    Button juliaButton("JULIA SET", {width_box, height_box}, 20, sf::Color::Black, sf::Color::Green);
    juliaButton.set_Font(TNR);
    juliaButton.set_Position({3 * width / 4 - width_box / 2, height / 2 - height_box / 2});

    double_stack saved_list;

    float zoom = 256.0f;
    int resolution = 100;
    int x_shift = -width / 2;
    int y_shift = -height / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pointmap[i * width + j].position = sf::Vector2f(j, i);
        }
    }

    while (window.isOpen())
    {
        bool flag = false;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (mandelButton.is_Mouse_Over(window))
                    {
                        flag = true;
                        chosen_graph = 1;
                    }
                    if (juliaButton.is_Mouse_Over(window))
                    {
                        flag = true;
                        chosen_graph = 2;
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
            }
        }

        window.clear();
        window.draw(pointmap);
        mandelButton.draw_To(window);
        juliaButton.draw_To(window);
        window.display();
        if (flag)
        {
            break;
        }
    }
    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);

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
                    resolution = min(4000.0, resolution + 200 * (zoom_factor - 1));
                }
                else if (event.mouseWheel.delta == -1)
                {
                    x_shift /= zoom_factor;
                    y_shift /= zoom_factor;
                    x_shift -= event.mouseWheel.x * (zoom_factor - 1) / zoom_factor;
                    y_shift -= event.mouseWheel.y * (zoom_factor - 1) / zoom_factor;
                    zoom /= zoom_factor;
                    resolution = max(100.0, resolution - 200 * (zoom_factor - 1));
                }
#pragma omp parallel for
                for (int i = 0; i < width * height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }
                generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                double zoom_factor = 2;
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    x_shift += (event.mouseWheel.x + x_shift) * (zoom_factor - 1);
                    y_shift += (event.mouseWheel.y + y_shift) * (zoom_factor - 1);
                    zoom *= zoom_factor;
                    resolution = min(4000.0, resolution + 200 * (zoom_factor - 1));
#pragma omp parallel for
                    for (int i = 0; i < width * height; i++)
                    {
                        pointmap[i].color = sf::Color::Black;
                    }
                    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    x_shift /= zoom_factor;
                    y_shift /= zoom_factor;
                    x_shift -= event.mouseWheel.x * (zoom_factor - 1) / zoom_factor;
                    y_shift -= event.mouseWheel.y * (zoom_factor - 1) / zoom_factor;
                    zoom /= zoom_factor;
                    resolution = max(100.0, resolution - 200 * (zoom_factor - 1));
//learn what is pragma
#pragma omp parallel for
                    for (int i = 0; i < width * height; i++)
                    {
                        pointmap[i].color = sf::Color::Black;
                    }
                    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    y_shift -= 10;
                    shift_image_up(pointmap, x_shift, y_shift, resolution, zoom, inversion);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    y_shift += 10;
                    shift_image_down(pointmap, x_shift, y_shift, resolution, zoom, inversion);
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    x_shift -= 10;
                    shift_image_left(pointmap, x_shift, y_shift, resolution, zoom, inversion);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {

                    x_shift += 10;
                    shift_image_right(pointmap, x_shift, y_shift, resolution, zoom, inversion);
                }
                else if (event.key.code == sf::Keyboard::R)
                {
                    cout << saved_list.get_size() << endl;
                    if (saved_list.get_size() <= 1)
                    {
                        continue;
                    }
                    int random = rand() % (saved_list.get_size() / 2);
                    int parity = rand() % 2;
                    for (int i = 0; i < random; i++)
                    {
                        if (parity)
                        {
                            saved_list.move_right();
                        }
                        else
                        {
                            saved_list.move_left();
                        }
                    }
                    image_sfml *image_pointer = new image_sfml();
                    cout << saved_list.return_current(image_pointer) << "\n";
                    image_pointer->retrieve_image_parameters(x_shift, y_shift, resolution, zoom, pointmap);
                    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                    delete image_pointer;
                }
                else if (event.key.code == sf::Keyboard::RBracket)
                {
                    cout << "Resolution Increased" << endl;
                    resolution = min(4000, resolution + 200);
                    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                }
                else if (event.key.code == sf::Keyboard::LBracket)
                {
                    cout << "Resolution Decreased" << endl;
                    resolution = max(100, resolution - 200);
                    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                }
                else if (event.key.code == sf::Keyboard::C)
                {
                    texture.create(window.getSize().x, window.getSize().y);
                    texture.update(window);
                    if (texture.copyToImage().saveToFile("Zoom- " + to_string(zoom) + ", Resolution- " + to_string(resolution) + ".jpg"))
                    {
                        cout << "Screenshot saved!" << endl;
                    }
                }
                else if (event.key.code == sf::Keyboard::H)
                {
                    cout << "Back to Home" << endl;

                    zoom = 256.0f;
                    resolution = 100;
                    x_shift = -width / 2;
                    y_shift = -height / 2;
                    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    cout << "Save Image in List" << endl;

                    saved_list.insert(x_shift, y_shift, resolution, zoom, pointmap);
                    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                }
                else if (event.key.code == sf::Keyboard::W)
                {
                    cout << "Load Last Saved Image" << endl;
                    image_sfml *image_pointer = new image_sfml();
                    cout << saved_list.return_current(image_pointer) << "\n";
                    image_pointer->retrieve_image_parameters(x_shift, y_shift, resolution, zoom, pointmap);
                    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                    delete image_pointer;
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    if (!saved_list.move_left())
                    {
                        cout << "Nowhere to move back!" << endl;
                        continue;
                    }
                    cout << "Move Back in the list" << endl;
                    image_sfml *image_pointer = new image_sfml();
                    cout << saved_list.return_current(image_pointer) << "\n";
                    image_pointer->retrieve_image_parameters(x_shift, y_shift, resolution, zoom, pointmap);

                    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                    delete image_pointer;
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    if (!saved_list.move_right())
                    {
                        cout << "Nowhere to move forward!" << endl;
                        continue;
                    }
                    cout << "Move Forward in the list" << endl;
                    image_sfml *image_pointer = new image_sfml();
                    cout << saved_list.return_current(image_pointer) << "\n";
                    image_pointer->retrieve_image_parameters(x_shift, y_shift, resolution, zoom, pointmap);
                    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                    delete image_pointer;
                }
                else if (event.key.code == sf::Keyboard::I)
                {
                    inversion = !inversion;
                    generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                }
                else if (event.key.code == sf::Keyboard::Q)
                {
                    while (saved_list.move_right())
                    {
                        ;
                    }
                    do
                    {
                        cout << "NEXT\n";
                        image_sfml *image_pointer = new image_sfml();
                        cout << saved_list.return_current(image_pointer) << "\n";
                        image_pointer->retrieve_image_parameters(x_shift, y_shift, resolution, zoom, pointmap);
                        generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                        window.clear();
                        window.draw(pointmap);
                        window.display();
                        sf::sleep(sf::milliseconds(2000));
                        delete image_pointer;
                    } while (saved_list.move_left());
                    do
                    {
                        cout << "NEXT\n";
                        image_sfml *image_pointer = new image_sfml();
                        cout << saved_list.return_current(image_pointer) << "\n";
                        image_pointer->retrieve_image_parameters(x_shift, y_shift, resolution, zoom, pointmap);
                        generate_graph(pointmap, x_shift, y_shift, resolution, zoom);
                        window.clear();
                        window.draw(pointmap);
                        window.display();
                        sf::sleep(sf::milliseconds(2000));
                        delete image_pointer;
                    } while (saved_list.move_right());
                }
                else if (event.key.code == sf::Keyboard::X)
                {
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(pointmap);
        window.display();
    }

    return 0;
}