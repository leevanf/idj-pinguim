#ifndef VEC2
#define VEC2
class Vec2{
public:
	float x;
	float y;
	Vec2();
	Vec2(float x, float y);
	Vec2& Add(Vec2 vector);
	Vec2& Add2(float x, float y);
	Vec2 AddAndReturn(Vec2 vector);
	Vec2& Subtract(Vec2 vector);
	Vec2& Subtract2(float x, float y);
	Vec2 SubtractAndReturn(Vec2 vector);
	Vec2& ScalarMultiply(float scalar);
	float Magnitude();
	Vec2& Normalize();
	Vec2 NormalizeAndReturn();
	float Distance(Vec2 vector);
	float InclinationXAxis();
	float InclinationXAxisDeg();
	float InclinationXAxisFromPoint(Vec2 vector);
	Vec2& Rotate(float theta);
	Vec2& RotateDeg(float thetaDeg);
	Vec2 ExtractSign();

	void Print();

	Vec2 operator+(Vec2 vector) { return Vec2(x + vector.x, y + vector.y); };
	Vec2 operator-(Vec2 vector) { return Vec2(x - vector.x, y - vector.y); };
	Vec2 operator*(float scalar) { return Vec2(x * scalar, y * scalar); };
	Vec2 operator/(float scalar) { return Vec2(x / scalar, y / scalar); };
	Vec2 operator*(const float rhs) const { return Vec2(x * rhs, y * rhs); };
};

#endif // VEC2