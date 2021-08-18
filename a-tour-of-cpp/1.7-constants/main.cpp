/*
 * constexpr specifies that the value of an object, variable and a function can be evaluated strictly at compile-time. And an expression can use in other constant expressions.
 */

int sum(int a, int b)
{
    return (a + b);
}

constexpr int sum_v2(int a, int b)
{
    return (a + b);
}

int main(void)
{
    const int a = 10;               // named constant
    int b = 11;                     // not a constant
    constexpr int c = 12;           // constant epression
    constexpr int i = a + c;        // OK
    constexpr int j = a + 1;        // OK
    const int m = sum(a, b);        // OK, run time assignment
    constexpr int n = sum_v2(a, 1); // OK, sum_v2 is a constexpr function
    /*
    constexpr int k = b + 1;        // "b" is not a constant
    constexpr int l = sum(a, b);    // not OK, constexpr will always accept a strictly compile-time value
     */
    return 0;
}
