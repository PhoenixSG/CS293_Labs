#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#define MAX_ITERATION 255

double isMandelbrot (double x, double y) {


    int i;
    int j;
    double Re[255];
    double Im[255];
    double a;
    double b;
    // double dist;
    double finaldist;
    int check;

    i=0;
    Re[0]=0;
    Im[0]=0;
    j=-1;
    a=0;
    b=0;

    while (i < MAX_ITERATION) {

        a = Re[j];
        b = Im[j];

        Re[i]=((a*a)-(b*b))+x;
        Im[i]=(2 * a * b) + y;

        i++;
        j++;
    }

    finaldist = sqrt(pow(Re[MAX_ITERATION],2)+pow(Im[MAX_ITERATION],2));

    if (finaldist > 2) { //not in mandelbrot
        check = 0;
    } else if (finaldist <= 2) { //in mandelbrot set
        check = 1;
    }

    return check;
}


int main()
{
    // sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    sf::RenderWindow window(sf::VideoMode(200, 200), "WORKS!", sf::Style::Close | sf::Style::Resize);

    


    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type = event.Closed){
                window.close();
            }
        }
    }

    return 0;
}