#pragma once
#include "SpriteComponent.h"
#include <vector>
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	// �ִϸ��̼��� �����Ӹ��� ���� (Component�� Update �޼��� �������̵�)
	void Update(float deltaTime) override;
	// �ִϸ��̼ǿ� ���Ǵ� �ý��� ����
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	// �ִϸ��̼� FPS�� ��ų� �����ϴ� �Լ�
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

private:
	// �ִϸ��̼ǿ� ���Ǵ� ��� �ý���
	std::vector<SDL_Texture*> mAnimTextures;
	// ���� ������
	float mCurrFrame;
	// �ִϸ��̼� ������ ����Ʈ
	float mAnimFPS;
};

