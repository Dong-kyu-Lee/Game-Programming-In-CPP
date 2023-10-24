#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder = 100)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{

}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
}
