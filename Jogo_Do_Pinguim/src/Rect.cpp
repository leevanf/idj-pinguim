#include "Rect.h"

Rect::Rect() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(float w, float h) {
	x = 0;
	y = 0;
	Rect::w = w;
	Rect::h = h;
}

Rect::Rect(float x, float y, float w, float h) {
	Rect::x = x;
	Rect::y = y;
	Rect::w = w;
	Rect::h = h;
}

void Rect::addVector(Vec2 vector) {
	x += vector.x;
	y += vector.y;
}

Vec2 Rect::RectCenter() {
	return Vec2(x + w / 2, y + h / 2);
}

void Rect::setRectCenter(float x, float y) {
	Rect::x = x - w / 2;
	Rect::y = y - h / 2;
}

void Rect::setRectCenter(Vec2 vector) {
	Rect::x = vector.x - w / 2;
	Rect::y = vector.y - h / 2;
}

float Rect::_DistanceCalculator(Vec2 firstRect, Vec2 secondRect) {
	float xPos = firstRect.x - secondRect.x;
	float yPos = firstRect.y - secondRect.y;
	return sqrt(pow(xPos, 2) + pow(yPos, 2));
}

float Rect::CentersDistance(Rect otherRect) {
	Vec2 currentRect = Rect::RectCenter();
	Vec2 secondRect = otherRect.RectCenter();
	return Rect::_DistanceCalculator(currentRect, secondRect);
}

bool Rect::isPointInsideRect(float pointX, float pointY) {
	if (pointX >= x && pointX <= (x + w)) {
		if (pointY >= y && pointY <= (y + h)) {
			return true;
		}
	}
	return false;
}