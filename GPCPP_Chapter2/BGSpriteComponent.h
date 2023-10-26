#pragma once
#include "SpriteComponent.h"
#include "Math.h"
class BGSpriteComponent :
    public SpriteComponent
{
public:
    BGSpriteComponent(Actor* owner, int drawOrder = 10);
    // SpriteComponent�κ��� �������̵��� Update/Draw �Լ�
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;
    // ��濡�� ���Ǵ� �ý��� ����
    void SetBGTextures(const std::vector<SDL_Texture*>& textures);
    // ȭ�� ũ�⸦ ��ų� ��ũ�� �ӵ����� ���� �� ��� ����
    void SetScreenSize(const Vector2& size) { mScreenSize = size; }
    void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
    float GetScrollSpeed() const { return mScrollSpeed; }

private:
    // �� ��� �̹����� ��� �̹����� ������
    struct BGTexture
    {
        SDL_Texture* mTexture;
        Vector2 mOffset;
    };
    std::vector<BGTexture> mBGTextures;
    Vector2 mScreenSize;
    float mScrollSpeed;
};

