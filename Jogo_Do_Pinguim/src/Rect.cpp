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

std::pair<float, float> Rect::RectCenter() {
	return std::make_pair(x+w/2,y+h/2);
}
/*
Para extrair a resposta:
std::pair<int, int> answer = ExampleRect.RectCenter();
  // -> answer.first == x+w/2
  // -> answer.second == y+h/2
*/

float Rect::_DistanceCalculator(std::pair<float, float> firstRect, std::pair<float, float> secondRect) {
	float xPos = firstRect.first - secondRect.first;
	float yPos = firstRect.second - secondRect.second;
	return sqrt(pow(xPos, 2) + pow(yPos, 2));
}

float Rect::CentersDistance(Rect otherRect) {
	std::pair<float, float> currentRect = Rect::RectCenter();
	std::pair<float, float> secondRect = otherRect.RectCenter();
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