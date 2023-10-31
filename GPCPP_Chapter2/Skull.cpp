#include "Skull.h"
#include "Game.h"
#include "AnimSpriteComponent.h"

Skull::Skull(Game* game)
	:Actor(game)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = 
	{
		game->GetTexture("Asset/Character01.png"),
		game->GetTexture("Asset/Character02.png"),
		game->GetTexture("Asset/Character03.png"),
		game->GetTexture("Asset/Character04.png"),
		game->GetTexture("Asset/Character05.png"),
		game->GetTexture("Asset/Character06.png"),
		game->GetTexture("Asset/Character07.png"),
		game->GetTexture("Asset/Character08.png"),
		game->GetTexture("Asset/Character09.png"),
		game->GetTexture("Asset/Character10.png"),
		game->GetTexture("Asset/Character11.png"),
		game->GetTexture("Asset/Character12.png"),
		game->GetTexture("Asset/Character13.png"),
		game->GetTexture("Asset/Character14.png"),
		game->GetTexture("Asset/Character15.png"),
		game->GetTexture("Asset/Character16.png"),
		game->GetTexture("Asset/Character17.png"),
		game->GetTexture("Asset/Character18.png")
	};
	asc->SetAnimTextures(anims);
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

	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 250.0f;
	}
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_SPACE])
	{

	}
}
