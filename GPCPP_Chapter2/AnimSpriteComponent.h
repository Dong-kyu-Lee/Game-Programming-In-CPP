#pragma once
#include "SpriteComponent.h"
#include <vector>
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	// 애니메이션을 프레임마다 갱신 (Component의 Update 메서드 오버라이드)
	void Update(float deltaTime) override;
	// 애니메이션에 사용되는 택스쳐 설정
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	// 애니메이션을 실행할 범위를 설정
	void SetAnimFrameRange(int start, int end);
	// 애니메이션 FPS를 얻거나 수정하는 함수
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

private:
	// 애니메이션에 사용되는 모든 택스쳐
	std::vector<SDL_Texture*> mAnimTextures;
	// 현재 프레임
	float mCurrFrame;
	// 애니메이션 프레임 레이트
	float mAnimFPS;
	// 그릴 프레임의 범위
	int mStartFrame;
	int mEndFrame;
};

