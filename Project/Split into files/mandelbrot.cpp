#include "complex.cpp"

int mandelbrot(long double x, long double y, int precision)
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
        if (z.get_magnitude() > 3)
            break;
    }
    return iterations;
}