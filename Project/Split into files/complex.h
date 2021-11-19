//This is the complex numbers class which allows for operations made on complex numbers.
//Several overloaded operators allows us to build concise and intuitive expressions.

class complex_num
{
private:
    long double real_part;
    long double imaginary_part;

public:
    complex_num(long double real, long double imaginary);
    complex_num();
    long double get_real();
    long double get_img();
    void set_real(long double real);
    void set_img(long double img);
    long double get_magnitude();
    long double get_magnitude_squared();
    long double get_angle();
    complex_num operator*(complex_num object);
    complex_num operator+(complex_num object);
    complex_num operator-(complex_num object);
};