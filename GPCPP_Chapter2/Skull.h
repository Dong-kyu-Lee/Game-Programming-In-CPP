#pragma once
#include "Actor.h"
#include "AnimSpriteComponent.h"

class Skull : public Actor
{
public:
	Skull(class Game* game);
	void UpdateActor(float deltaTime) override;
	void PressKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }

	enum AnimState { IDLE, WALK, JUMP, ATTACK, };
private:
	AnimSpriteComponent* mAnim;
	AnimState mAnimState;
	float mRightSpeed;
	float mDownSpeed;
};

