#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    int i = 32;
    float j = 32;
    double k = 32;
    auto fp = [](const auto &n)->auto { return n * 2; };
    auto x = fp(i);
    auto y = fp(j);
    auto z = fp(k);

    cout << "Value of X: " << x << ", type of X: " << typeid(x).name() << endl;
    cout << "Value of Y: " << y << ", type of Y: " << typeid(y).name() << endl;
    cout << "Value of Z: " << z << ", type of Z: " << typeid(z).name() << endl;

    return 0;
}

/**
 * Output:
 *
 * Value of X: 64, type of X: i
 * Value of Y: 64, type of Y: f
 * Value of Z: 64, type of Z: d
 */
