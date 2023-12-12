#include "InputComponent.h"

InputComponent::InputComponent(Actor* actor)
	:MoveComponent(actor)
	, mForwardKey(0)
	, mBackKey(0)
	, mClockwiseKey(0)
	, mCounterClockwiseKey(0)
{
}

// MoveComponent를 위한 이동, 회전 속도 계산
void InputComponent::ProcessInput(const uint8_t* keyState)
{
	float forwardSpeed = 0.0f;
	if (keyState[mForwardKey])
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	if (keyState[mBackKey])
	{
		forwardSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}
