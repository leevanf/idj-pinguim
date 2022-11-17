#ifndef RECT
#define RECT
#include <utility>
#include "Vec2.h"

class Rect{
public:
	float x;
	float y;
	float w;
	float h;
	Rect();
	Rect(float w, float h);
	Rect(float x, float y, float w, float h);
	void addVector(Vec2 vector);
	std::pair<float, float> RectCenter();
	float CentersDistance(Rect otherRect);
	bool isPointInsideRect(float x, float y);
private:
	float _DistanceCalculator(std::pair<float, float> firstRect, std::pair<float, float> secondRect);
};

#endif // RECT