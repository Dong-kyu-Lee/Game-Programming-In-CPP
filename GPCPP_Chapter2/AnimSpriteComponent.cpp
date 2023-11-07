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
		// 선택한 범위의 시작 프레임과 끝 프레임의 텍스쳐를 전달한다
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
