#include "point.h"
#define TRACE
#include "../trace.h"

Point::Point():m_X{0}, m_Y{0} {
	TRACETHIS;
}

Point::Point(int x, int y):m_X{x}, m_Y{y} {
	TRACETHIS;
}

Point::Point(const Point &pt):m_X{pt.m_X}, m_Y{pt.m_Y} {
	TRACETHIS;
}

Point::~Point() {
	TRACETHIS;
}
