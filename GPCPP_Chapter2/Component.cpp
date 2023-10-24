#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder = 100)
	:mOwner(owner)
	,mUpdateOrder(updateOrder)
{
	mOwner->AddCompoment(this);
}
Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime) {}