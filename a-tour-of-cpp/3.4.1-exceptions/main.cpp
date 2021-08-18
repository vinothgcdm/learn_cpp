/*
 * There is no fundamental difference between a struct and a class; a struct is simply
 * a class with members public by default.
 */
#include <iostream>
#include <stdexcept>

class Vector {
public:
    Vector(int s) :elem{new double[s]}, sz{s}
    {
    }
    
    double& operator[](int i)
    {
        if ((i < 0) || (i >= size()))
        {
            throw std::out_of_range {"Vector::operator[]"};
        }

        return elem[i];
    }
    int size() noexcept
    {
        /*
         * terminate called after throwing an instance of 'std::out_of_range'
         *   what():  Vector::operator[]
         *   Aborted
         */
        //throw std::out_of_range {"Vector::operator[]"};
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
    try {
        v[v.size()] = 90;
    }
    catch (std::out_of_range)
    {
        std::cout << "Out of range.!" << '\n';
    }

    std::cout << "Vector size: " << v.size() << '\n';
    std::cout << v[0] << "\n" ;
    std::cout << v[1] << "\n" ;
    std::cout << v[2] << "\n" ;
    return 0;
}
