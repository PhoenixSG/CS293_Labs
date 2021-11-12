#include "complex.cpp"

int julia(long double x, long double y, int precision, complex_num constant)
{
    complex_num z(x, y);
    // point is a constant used to compute the julia set
    complex_num point = constant;
    // point = complex_num(0.285, 0.01);
    // point = complex_num(-0.7269, 0.1889);
    // point = complex_num(-0.8, 0.156);
    // point = complex_num(-0.4, 0.6);
    int iterations = 0; //keep track of the number of iterations
    for (int k = 0; k < precision; k++)
    {
        z = z * z;
        z = z + point;
        iterations++;
        long double magnitude = z.get_magnitude();
        if (magnitude > 3)
           return iterations + 1 - log(log2(magnitude));
    }
    return iterations;
}