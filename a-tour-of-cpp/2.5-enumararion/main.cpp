#include <iostream>

int main(void)
{
#if 0  // 1. Two enum cannot share the same names.
 
    enum Color {
        red,
        blue,
        orange
    };
    enum Traffic_light {
        green,
        yellow,
        red  // redeclaration of ‘red’. previous declaration ‘main()::Color red’.
    };
#endif

#if 0  // 2. No variable can have a name which is already in some enumaration
    enum Color {
        red,
        blue,
        orange
    };
    int red;  // error: ‘int red’ redeclared as different kind of symbol
#endif

#if 0  // 3. Enums are not type-safe
    enum Color {
        white,
        blue,
        orange
    };
    enum Traffic_light {
        green,
        yellow,
        red  // redeclaration of ‘red’. previous declaration ‘main()::Color red’.
    };
   Color c1 = white;
   Traffic_light c2 = green;

   if (c1 == c2)
       std::cout << "Equal" << '\n';
#endif

#if 1
    /* ENUMARATION CLASS */
    enum class Color {
        red,
        blue,
        orange
    };
    enum class Traffic_light {
        green,
        yellow,
        red
    };
   Color c1 = Color::red;
   Traffic_light c2 = Traffic_light::green;

   //if (c1 == c2)
   //    std::cout << "Equal" << '\n';
#endif
    return 0;
}
