#include "CircleComponent.h"

CircleComponent::CircleComponent(Actor* owner)
    :Component(owner)
    ,mRadius(0.0f)
{
}

float CircleComponent::GetRadius() const
{
    return mOwner->GetScale() * mRadius;
}

const Vector2& CircleComponent::GetCenter() const
{
    return mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    Vector2 diff = a.GetCenter() - b.GetCenter();
    float diffSq = diff.LengthSq();
    float radiusSq = a.GetRadius() + b.GetRadius();
    radiusSq *= radiusSq;
    return  diffSq <= radiusSq;
}