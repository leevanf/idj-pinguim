#include "Camera.h"
#include "Collider.h"
#include "Game.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component{ associated } {
	Collider::scale = scale;
	Collider::offset = offset;
}

void Collider::Update(float dt) {
	Rect tempBox = mAssociated.box;
	box = tempBox.multiplyByScale(scale).setRectCenter(mAssociated.box.RectCenter() + offset.RotateDeg(mAssociated.angleDeg));
}

void Collider::Render() {
	Vec2 center(box.RectCenter());
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).Rotate(mAssociated.angleDeg * M_PI / 180) + center + Camera::pos;
	points[0] = { (int)point.x, (int)point.y };
	points[4] = { (int)point.x, (int)point.y };

	point = (Vec2(box.x + box.w, box.y) - center).Rotate(mAssociated.angleDeg * M_PI / 180) + center + Camera::pos;
	points[1] = { (int)point.x, (int)point.y };

	point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate(mAssociated.angleDeg * M_PI / 180) + center + Camera::pos;
	points[2] = { (int)point.x, (int)point.y };

	point = (Vec2(box.x, box.y + box.h) - center).Rotate(mAssociated.angleDeg * M_PI / 180) + center + Camera::pos;
	points[3] = { (int)point.x, (int)point.y };

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);

}