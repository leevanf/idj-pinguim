#include "GameObject.h"
#include <iostream>

GameObject::GameObject() {
	isDead = false;
	started = false;
}

GameObject::~GameObject() {
	for (auto it = (components.end() - 1); it != (components.begin() - 1); --it) {
		delete* it;
	}
	components.clear();
}

void GameObject::Start() {
	for (int counter = 0; counter < components.size(); counter++) {
		components[counter]->Start();
	}
	started = true;
}

void GameObject::Update(float dt) {
	for (auto it = components.begin(); it != components.end(); ++it) {
		(*it)->Update(dt);
	}
}

void GameObject::Render() {
	for (auto it = components.begin(); it != components.end(); ++it) {
		(*it)->Render();
	}
}

bool GameObject::IsDead() {
	return isDead;
}

void GameObject::RequestDelete() {
	isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
	components.emplace_back(cpt);
	if (started) {
		cpt->Start();
	}
}

void GameObject::RemoveComponent(Component* cpt) {
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == cpt) {
			components.erase(it);
		}
	}
}

Component* GameObject::GetComponent(std::string type) {
	for (auto it = components.begin(); it != components.end(); ++it) {
		if ((*it)->Is(type)) {
			return *it;
		}
	}
	return nullptr;
}