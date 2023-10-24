#pragma once
#include "Component.h"
#include "SDL.h"
class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	//Getter
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

protected:
	//그릴 택스쳐
	SDL_Texture* mTexture;
	// 그리기 순서
	int mDrawOrder;
	// 택스쳐의 너비/높이
	int mTexWidth;
	int mTexHeight;
};
