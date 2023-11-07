#include "Asteroid.h"
#include "Random.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Asteroid::Asteroid(Game* game)
	:Actor(game)
{
	Vector2 pos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	SetPosition(pos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Astroid.png"));
	// �̵� ������Ʈ�� �����ϰ� ���� �ӵ��� �����Ѵ�.
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.f);
}

Asteroid::~Asteroid()
{
}
