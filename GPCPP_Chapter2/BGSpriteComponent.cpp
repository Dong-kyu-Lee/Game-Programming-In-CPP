#include "BGSpriteComponent.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{

}
