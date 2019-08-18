#include <iostream>

class Point {
	int m_X;
	int m_Y;
public:
	Point();
	Point(int x, int y);
	Point(const Point &pt);
	~Point();
	int GetX() const {
		return m_X;
	}
	int GetY() const {
		return m_Y;
	}
};
