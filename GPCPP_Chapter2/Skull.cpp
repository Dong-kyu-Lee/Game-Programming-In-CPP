#include "Skull.h"
#include "Game.h"

Skull::Skull(Game* game)
	:Actor(game)
	, mAnim(nullptr)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
	, mAnimState(AnimState::IDLE)
{
	mAnim = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = 
	{
		game->GetTexture("Assets/Character01.png"),
		game->GetTexture("Assets/Character02.png"),
		game->GetTexture("Assets/Character03.png"),
		game->GetTexture("Assets/Character04.png"),
		game->GetTexture("Assets/Character05.png"),
		game->GetTexture("Assets/Character06.png"),
		game->GetTexture("Assets/Character07.png"),
		game->GetTexture("Assets/Character08.png"),
		game->GetTexture("Assets/Character09.png"),
		game->GetTexture("Assets/Character10.png"),
		game->GetTexture("Assets/Character11.png"),
		game->GetTexture("Assets/Character12.png"),
		game->GetTexture("Assets/Character13.png"),
		game->GetTexture("Assets/Character14.png"),
		game->GetTexture("Assets/Character15.png"),
		game->GetTexture("Assets/Character16.png"),
		game->GetTexture("Assets/Character17.png"),
		game->GetTexture("Assets/Character18.png")
	};
	mAnim->SetAnimTextures(anims);
	mAnim->SetAnimFrameRange(0, 1);
}

void Skull::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;

	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 1000.0f)
	{
		pos.x = 1000.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}

	SetPosition(pos);
}

void Skull::PressKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;

	if (state[SDL_SCANCODE_A])
	{
		if (mAnimState != WALK)
		{
			mAnim->SetAnimFrameRange(0, 5);
			mAnimState = WALK;
		}
		mRightSpeed -= 250.0f;
	}
	if (state[SDL_SCANCODE_D])
	{
		if (mAnimState != WALK)
		{
			mAnim->SetAnimFrameRange(0, 5);
			mAnimState = WALK;
		}
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		if (mAnimState != WALK)
		{
			mAnim->SetAnimFrameRange(0, 5);
			mAnimState = WALK;
		}
		mDownSpeed -= 250.0f;
	}
	if (state[SDL_SCANCODE_S])
	{
		if (mAnimState != WALK)
		{
			mAnim->SetAnimFrameRange(0, 5);
			mAnimState = WALK;
		}
		mDownSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		if (mAnimState != ATTACK)
		{
			mAnim->SetAnimFrameRange(15, 17);
			mAnimState = ATTACK;
		}
	}
}
