#pragma once
#include <cmath>

template <class T>
class Vec2
{
public:
	T x, y;

	Vec2() {}
	Vec2(T _x) : x(_x), y(_x) {}
	Vec2(T _x, T _y) : x(_x), y(_y) {}

	Vec2 operator+(Vec2& v) { return Vec2(x + v.x, y + v.y); }
	Vec2 operator-(Vec2& v) { return Vec2(x - v.x, y - v.y); }
	Vec2 operator*(Vec2& v) { return Vec2(x * v.x, y * v.y); }
	Vec2 operator/(Vec2& v) { return Vec2(x / v.x, y / v.y); }

	bool operator==(const Vec2& v) { return (x == v.x && y == v.y); }

	T magnitude() { return std::sqrt((x * x) + (y * y)); }
	T angle() { return std::atan(y / x); }
	
	~Vec2() {}
};

