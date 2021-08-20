#include <iostream>

class Vector {
public:
    Vector(int s) :elem{new double[s]}, sz{s} { }
    double& operator[](int i) { return elem[i]; }
    int size() const { return sz; }
private:
    double* elem;
    int sz;
};

/* Abstract class */
class Container {
public:
    virtual double& operator[](int) = 0;
    virtual int size() const = 0;
    virtual ~Container() { std::cout << "Base class distructor" << '\n'; }
};

/* Derived class */
class Vector_container :public Container
{
private:
    Vector v;
public:
    Vector_container(int s) :v{s} {}
    /* Base class disctructor implicitly invoked by this derived class distructor */
    ~Vector_container() { std::cout << "Derived class distructor" << '\n'; }
    double& operator[](int i) { return v[i]; }
    int size() const { return v.size(); }
};

int main(void)
{
    Vector_container a(10);
    return 0;
}
