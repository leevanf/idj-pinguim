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
	Vec2 RectCenter();
	Rect& setRectCenterX(float x);
	Rect& setRectCenterY(float y);
	Rect& setRectCenter(float x, float y);
	Rect& setRectCenter(Vec2 vector);
	Rect& multiplyByScale(Vec2 scale);
	float CentersDistance(Rect otherRect);
	bool isPointInsideRect(float x, float y);
private:
	float _DistanceCalculator(Vec2 firstRect, Vec2 secondRect);
};

#endif // RECT