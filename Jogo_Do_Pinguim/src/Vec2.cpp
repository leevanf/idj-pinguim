#define _USE_MATH_DEFINES
#include "Vec2.h"
#include <cmath>
#include <iostream>

Vec2::Vec2() {
	x = 0;
	y = 0;
}

Vec2::Vec2(float x, float y) {
	Vec2::x = x;
	Vec2::y = y;
}

Vec2& Vec2::Add(Vec2 vector) {
	Vec2::x += vector.x;
	Vec2::y += vector.y;
	return *this;
}

Vec2& Vec2::Add2(float x, float y) {
	Vec2::x += x;
	Vec2::y += y;
	return *this;
}

Vec2 Vec2::AddAndReturn(Vec2 vector) {
	Vec2 newVector(x + vector.x, y + vector.y);
	return newVector;
}

Vec2& Vec2::Subtract(Vec2 vector) {
	Vec2::x -= vector.x;
	Vec2::y -= vector.y;
	return *this;
}

Vec2& Vec2::Subtract2(float x, float y) {
	Vec2::x -= x;
	Vec2::y -= y;
	return *this;
}

Vec2 Vec2::SubtractAndReturn(Vec2 vector) {
	Vec2 newVector(x - vector.x, y - vector.y);
	return newVector;
}

Vec2& Vec2::ScalarMultiply(float scalar) {
	Vec2::x *= scalar;
	Vec2::y *= scalar;
	return *this;
}

float Vec2::Magnitude() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2& Vec2::Normalize() {
	float currentMagnitude = Vec2::Magnitude();
	if (currentMagnitude != 0) {
		x /= currentMagnitude;
		y /= currentMagnitude;
	}
	else {
		x = 0;
		y = 0;
	}
	return *this;
}

Vec2 Vec2::NormalizeAndReturn() {
	float currentMagnitude = Vec2::Magnitude();
	Vec2 normalizedVector(x/currentMagnitude, y/currentMagnitude);
	return normalizedVector;
}

float Vec2::Distance(Vec2 vector) {
	Vec2 temp(x - vector.x, y - vector.y);
	return temp.Magnitude();
}

float Vec2::InclinationXAxis() {
	return atan2(y, x);
}

float Vec2::InclinationXAxisDeg() {
	return (atan2(y, x) * 180 / M_PI);
}

float Vec2::InclinationXAxisFromPoint(Vec2 vector) {
	float x = vector.x - Vec2::x;
	float y = vector.y - Vec2::y;
	return atan2(y, x);
}

Vec2& Vec2::Rotate(float theta) {
	float newX = x * cos(theta) - y * sin(theta);
	float newY = y * cos(theta) + x * sin(theta);
	x = newX;
	y = newY;
	return *this;
}

Vec2& Vec2::RotateDeg(float thetaDeg) {
	float theta = thetaDeg * M_PI / 180;
	float newX = x * cos(theta) - y * sin(theta);
	float newY = y * cos(theta) + x * sin(theta);
	x = newX;
	y = newY;
	return *this;
}

Vec2 Vec2::ExtractSign() {
	return Vec2(copysign(1, x), copysign(1, y));
}

void Vec2::Print() {
	std::cout << "x: " << x << " y: " << y << "\n";
}