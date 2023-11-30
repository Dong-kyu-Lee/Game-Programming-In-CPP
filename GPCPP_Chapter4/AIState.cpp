#include "AIState.h"

AIPatrol::AIPatrol(AIComponent* owner)
	:AIState(owner)
{
}

void AIPatrol::Update(float deltaTime)
{
	// 일부 갱신 작업
	// ...
	SDL_Log("Updating %s state", GetName());
	bool dead = false; // 자신이 죽었는지 판단
	if (dead)
	{
		mOwner->ChangeState("Death");
	}
}

void AIPatrol::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
}

void AIPatrol::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
}

AIDeath::AIDeath(AIComponent* owner)
	:AIState(owner)
{
}

void AIDeath::Update(float deltaTime)
{
	SDL_Log("Updating %s state", GetName());
}

void AIDeath::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
}

void AIDeath::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
}

AIAttack::AIAttack(AIComponent* owner)
	:AIState(owner)
{
}

void AIAttack::Update(float deltaTime)
{
	SDL_Log("Updating %s state", GetName());
}

void AIAttack::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
}

void AIAttack::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
}
