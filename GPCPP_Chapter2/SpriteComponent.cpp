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
		// �ؽ��ĸ� �׸� �簢�� ����
		SDL_Rect r;
		// �������� ��ĳ��(����) ������ �ʺ�/���� ��ȯ
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		// �������� ��ġ�� �߽����� �簢�� ��ġ
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		// ��������Ʈ�� �׸���.
		SDL_RenderCopyEx(
			renderer,
			mTexture,	// �׸� �ý���
			nullptr,	// �׸� �ý��� ����, nullptr�̸� ��ü ����
			&r,			// �׷��� �������� �簢�� ����
			-Math::ToDegrees(mOwner->GetRotation()), // (������ ������ ��ȯ)
			nullptr,	// ȸ�� ������
			SDL_FLIP_NONE // �ø� �ൿ
		);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// �ؽ����� �ʺ�� ���̸� ����
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
