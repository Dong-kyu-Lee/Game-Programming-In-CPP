#pragma once
#include "Actor.h"
class Skull : public Actor
{
public:
	Skull(class Game* game);
	void UpdateActor(float deltaTime) override;
	void PressKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
private:
	float mRightSpeed;
	float mDownSpeed;
};

