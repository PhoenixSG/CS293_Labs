#ifndef complex_class
#define complex_class

#include <math.h>
#include "complex.h"

complex_num::complex_num(long double real, long double imaginary)
{
    real_part = real;
    imaginary_part = imaginary;
}
complex_num::complex_num()
{
    real_part = 0;
    imaginary_part = 0;
}
long double complex_num::get_real()
{
    return real_part;
}
long double complex_num::get_img()
{
    return imaginary_part;
}
void complex_num::set_real(long double real)
{
    real_part = real;
}
void complex_num::set_img(long double img)
{
    imaginary_part = img;
}
long double complex_num::get_magnitude()
{
    return sqrt(real_part * real_part + imaginary_part * imaginary_part);
}

//This function prevents the use of sqrt() function for the magnitude and helps speeden up the calculation
long double complex_num::get_magnitude_squared()
{
    return real_part * real_part + imaginary_part * imaginary_part;
}
long double complex_num::get_angle()
{
    return atan(imaginary_part / real_part);
}
complex_num complex_num::operator*(complex_num object)
{
    complex_num product;
    product.set_real(real_part * object.get_real() - imaginary_part * object.get_img());
    product.set_img(real_part * object.get_img() + imaginary_part * object.get_real());
    return product;
}
complex_num complex_num::operator+(complex_num object)
{
    complex_num sum;
    sum.set_real(real_part + object.get_real());
    sum.set_img(imaginary_part + object.get_img());
    return sum;
}
complex_num complex_num::operator-(complex_num object)
{
    complex_num sum;
    sum.set_real(real_part - object.get_real());
    sum.set_img(imaginary_part - object.get_img());
    return sum;
}
#endif
