#pragma once
#include "AIState.h"
class AIPatrol : public AIState
{
public:
	AIPatrol(class AIComponent* owner);

	// 이 상태에 대한 행위를 재정의
	virtual void Update(float deltaTime) override;

	virtual void OnEnter() override;

	virtual void OnExit() override;

	virtual const char* GetName() const override
	{
		return "Patrol";
	};

};

