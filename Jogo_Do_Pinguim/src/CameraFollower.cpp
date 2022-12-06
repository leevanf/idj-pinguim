#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go) {

}

void CameraFollower::Update(float dt) {
	mAssociated.box.x = -Camera::pos.x;
	mAssociated.box.y = -Camera::pos.y;
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(std::string type) {
	return (type == "CameraFollower");
}