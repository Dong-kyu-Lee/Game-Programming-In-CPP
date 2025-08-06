#pragma once
#include "AIState.h"
class AIPatrol : public AIState
{
public:
	AIPatrol(class AIComponent* owner);

	// �� ���¿� ���� ������ ������
	virtual void Update(float deltaTime) override;

	virtual void OnEnter() override;

	virtual void OnExit() override;

	virtual const char* GetName() const override
	{
		return "Patrol";
	};

};

