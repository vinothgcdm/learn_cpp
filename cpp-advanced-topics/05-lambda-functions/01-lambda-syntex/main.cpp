/**
 * Lambda capture:
 * ---------------
 * [var]        Capture var by value
 * [&var]       Capture var by reference
 * [&var, var2] Capture var by reference, and var2 by value
 * [=]          Capture all variables by value
 * [=, &var]    Capture all by value, and var by reference
 * [&]          Capture all variables by reference
 * [&, var]     Capture all by reference, except capture var by value
 */
#include <cstdio>
#include <locale>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

constexpr size_t maxlen = 128;

int main()
{
    char s[] = "big light in sky slated to appear in east";
    char lastc = 0;
    char lastd = 'X';
    char laste = 'X';

    transform(s, s + strnlen(s, maxlen), s, [=](const char &c)mutable->char {
        const char r = (lastc == ' ' || lastc == 0) ? toupper(c) : tolower(c);
        lastc = c;
        lastd = 'A';
        laste = 'B';
        return r;
    });
    puts(s);
    cout << lastd << ", " << laste << endl;
}
