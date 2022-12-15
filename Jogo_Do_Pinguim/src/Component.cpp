#include "Component.h"

Component::Component(GameObject& associated) : mAssociated{associated} {}

void Component::Start() {}