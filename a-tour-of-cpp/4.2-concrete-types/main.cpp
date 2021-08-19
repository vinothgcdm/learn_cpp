#include <iostream>

class complex {
private:
    double re, im;
public:
    complex(double r, double i) :re{r}, im{i} {}
    complex(double r) :re{r}, im{0} {}
    complex() :re{0}, im{0} {}

    double real() const { return re; }
    void real(double r) { re = r; }
    double imag() const { return im; }
    void imag(double i) { im = i; }

    complex& operator+=(complex z) { re += z.re; im += z.im; return *this; }
    complex& operator-=(complex z) { re -= z.re; im -= z.im; return *this; }
    complex& operator*=(complex z);
    complex& operator/=(complex z);
};

complex& complex::operator*=(complex z) { re *= z.re; im *= z.im; return *this; }
complex& complex::operator/=(complex z) { re /= z.re; im /= z.im; return *this; }

/* error: ‘int operator+(int, int)’ must have an argument of class or enumerated type */
//int operator+(int a, int b) { return (a + b) }

complex operator+(complex a, complex b) { return a += b; }
complex operator-(complex a, complex b) { return a -= b; }
complex operator*(complex a, complex b) { return a *= b; }
complex operator/(complex a, complex b) { return a /= b; }
complex operator-(complex a) { complex x(-a.real(), -a.imag()); return x; }

int main(void)
{
    complex a(1,1), b(2,2);
    a += b;
    std::cout << "Real: " << a.real() << ", Imag: " << a.imag() << '\n';
    std::cout << "Real: " << b.real() << ", Imag: " << b.imag() << '\n';

    a = a + b;
    std::cout << "Real: " << a.real() << ", Imag: " << a.imag() << '\n';

    a = -a;
    std::cout << "Real: " << a.real() << ", Imag: " << a.imag() << '\n';
    return 0;
}
