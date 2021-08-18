/*
 * There is no fundamental difference between a struct and a class; a struct is simply
 * a class with members public by default.
 */
#include <iostream>

class Vector {
public:
    Vector(int s) :elem{new double[s]}, sz{s}
    {
    }
    
    double& operator[](int i)
    {
        return elem[i];
    }
    int size()
    {
        return sz;
    }
private:
    double* elem;
    int sz;
};

int main(void)
{
    Vector v(3);

    v[0] = 123;
    v[1] = 124;
    v[2] = 125;

    std::cout << "Vector size: " << v.size() << '\n';
    std::cout << v[0] << "\n" ;
    std::cout << v[1] << "\n" ;
    std::cout << v[2] << "\n" ;
    return 0;
}
