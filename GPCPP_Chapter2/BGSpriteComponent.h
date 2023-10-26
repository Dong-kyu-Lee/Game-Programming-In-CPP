#pragma once
#include "SpriteComponent.h"
#include "Math.h"
class BGSpriteComponent :
    public SpriteComponent
{
public:
    BGSpriteComponent(Actor* owner, int drawOrder = 10);
    // SpriteComponent로부터 오버라이딩한 Update/Draw 함수
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;
    // 배경에서 사용되는 택스쳐 설정
    void SetBGTextures(const std::vector<SDL_Texture*>& textures);
    // 화면 크기를 얻거나 스크롤 속도값을 설정 및 얻는 변수
    void SetScreenSize(const Vector2& size) { mScreenSize = size; }
    void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
    float GetScrollSpeed() const { return mScrollSpeed; }

private:
    // 각 배경 이미지와 배경 이미지의 오프셋
    struct BGTexture
    {
        SDL_Texture* mTexture;
        Vector2 mOffset;
    };
    std::vector<BGTexture> mBGTextures;
    Vector2 mScreenSize;
    float mScrollSpeed;
};

