#ifndef MANDELBROT
#define MANDELBROT

#include "complex.cpp"
#include "mandelbrot_coloring.cpp"

//This is the main function of the mandelbrot set.
//This calculates the number of iterations a point can be squared and shifted by a predefined algo, before it passes a threshold
//The number of iterations gives the value of that point.
//This value is then converted to a colour and thus, we see the graph

//We have also introduced variable level of precision which allows for a better tradeoff between time taken and accuracy.


int in_mandelbrot(long double x, long double y, int precision)
{
    complex_num point;
    point.set_real(x);
    point.set_img(y);
    complex_num z = point;
    int iterations = 0; //keep track of the number of iterations
    for (int k = 0; k < precision; k++)
    {
        complex_num z_new;
        z_new = z * z;
        z_new = z_new + point;
        z = z_new;
        iterations++;
        if (z.get_magnitude_squared() > 4)
            break;
    }
    return iterations;
}
#endif