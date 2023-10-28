#include "BGSpriteComponent.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	// x의 오프셋 값 갱신
	for (auto bg : mBGTextures)
	{
		bg.mOffset.x -= mScrollSpeed * deltaTime;

		if (bg.mOffset.x < -mScreenSize.x)
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		// 각 텍스처의 오프셋은 화면의 너비 * count다.
		temp.mOffset.x = mScreenSize.x * count;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}
