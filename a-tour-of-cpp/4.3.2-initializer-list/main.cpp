/*
 * There is no fundamental difference between a struct and a class; a struct is simply
 * a class with members public by default.
 */
#include <iostream>

class Vector {
public:
    Vector(std::initializer_list<double> list) :elem{new double[list.size()]}, sz{static_cast<int>(list.size())}
    {
        std::copy(list.begin(), list.end(), elem);
    }
    Vector(int s) :elem{new double[s]}, sz{s} { }
    double& operator[](int i) { return elem[i]; }
    int size() { return sz; }
private:
    double* elem;
    int sz;
};

int main(void)
{
    Vector v({1, 2, 3});

    std::cout << "Vector size: " << v.size() << '\n';
    std::cout << v[0] << "\n" ;
    std::cout << v[1] << "\n" ;
    std::cout << v[2] << "\n" ;
    return 0;
}
