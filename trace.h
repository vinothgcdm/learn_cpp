#include <iostream>
#ifdef TRACE
#define TRACETHIS (std::cout << __PRETTY_FUNCTION__ << std::endl)
#else
#define TRACETHIS
#endif
