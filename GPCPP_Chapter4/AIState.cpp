#include "AIState.h"

AIPatrol::AIPatrol(AIComponent* owner)
	:AIState(owner)
{
}

void AIPatrol::Update(float deltaTime)
{
	// �Ϻ� ���� �۾�
	// ...
	SDL_Log("Updating %s state", GetName());
	bool dead = false; // �ڽ��� �׾����� �Ǵ�
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
