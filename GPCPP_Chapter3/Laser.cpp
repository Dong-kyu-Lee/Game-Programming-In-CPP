#include "Laser.h"
#include "SpriteComponent.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "Asteroid.h"
#include "Game.h"

Laser::Laser(Game* game)
	:Actor(game)
	,mDeadTimer(1.0f)
{
	SpriteComponent* sc = new SpriteComponent(this, 99);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())))
		{
			SetState(EDead);
			ast->SetState(EDead);
			break;
		}
	}
}
