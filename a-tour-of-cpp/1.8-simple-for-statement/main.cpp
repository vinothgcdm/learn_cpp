#include <iostream>

int main(void)
{
    int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (auto x: v)  // for each x in v
        std::cout << x << '\n';

    for (auto x:{10, 20, 30, 40, 50})
        std::cout << x << '\n';

    /*
     * 1. In a declaration, the unary suffix & means "reference to".
     * 2. Areference is similar to a pointer, except that you don't need to use a prefix *
     *    to access the value referred to by the reference.
     * 3. A reference cannot be made to refer to a different object after its initialization.
     */
    for (auto& x: v)
        std::cout << x << '\n';

    int a = 1;
    int b = 2;
    int& c = a;
    c = 343;  // It changing the value of a.
    std::cout << a << " : " << b << " : " << c << '\n';

    return 0;
}

