#include "SpriteComponent.h"
#include "Actor.h"

SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		// 텍스쳐를 그릴 사각형 영역
		SDL_Rect r;
		// 소유자의 스캐일(배율) 값으로 너비/높이 변환
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		// 소유자의 위치를 중심으로 사각형 배치
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		// 스프라이트를 그린다.
		SDL_RenderCopyEx(
			renderer,
			mTexture,	// 그릴 택스쳐
			nullptr,	// 그릴 택스쳐 영역, nullptr이면 전체 영역
			&r,			// 그려질 목적지의 사각형 영역
			-Math::ToDegrees(mOwner->GetRotation()), // (라디안을 각도로 변환)
			nullptr,	// 회전 기준점
			SDL_FLIP_NONE // 플립 행동
		);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// 텍스쳐의 너비와 높이를 얻자
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
