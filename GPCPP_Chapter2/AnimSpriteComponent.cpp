#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,mCurrFrame(0)
	,mAnimFPS(10.0f)
	,mStartFrame(0)
	,mEndFrame(0)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		mCurrFrame += mAnimFPS * deltaTime;

		while (mCurrFrame >= mEndFrame + 1)
		{
			mCurrFrame -= (mEndFrame - mStartFrame);
		}

		// 현재 택스처 설정
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	
	if (mAnimTextures.size() > 0)
	{
		mCurrFrame = 0.0f;
		SetTexture(textures[mCurrFrame]);
	}
}

void AnimSpriteComponent::SetAnimFrameRange(int startIndex, int endIndex)
{
	if (mAnimTextures.size() > 0)
	{
		// 이미 실행중인 애니메이션의 프레임인지 판단하는 조건문
		/*if (mCurrFrame > startIndex && mCurrFrame < endIndex)
			return;*/

		if (startIndex >= 0)
		{
			mStartFrame = startIndex;
			mCurrFrame = mStartFrame;
		}
		if (endIndex < mAnimTextures.size())
		{
			mEndFrame = endIndex;
		}
	}
}
