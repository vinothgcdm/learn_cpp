#include "point.h"
#include <iostream>
/*
 * This is the three way to call copy constructor.
 * 1) Object initialization with another object.
 * 2) Object pass by value.
 * 3) Object return by value.
 */
Point ShowPoint(const Point &p) {
	std::cout << p.GetX() << ", " << p.GetY() << std::endl;
	return p;  // Call copy constructor
}

int main() {
	Point p1{1, 2};  // Call copy constructor
	Point p2{p1};  // Call copy constructor
	ShowPoint(p2);
}
