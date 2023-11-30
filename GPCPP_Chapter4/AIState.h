#pragma once
#include "AIComponent.h"

class AIState
{
public:
	AIState(AIComponent* owner)
		: mOwner(owner)
	{}
	// 각 상태의 구체적인 행동
	virtual void Update(float deltaTime) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	// 상태의 이름 얻기
	virtual const char* GetName() const = 0;

protected:
	AIComponent* mOwner;
};

class AIPatrol :
	public AIState
{
public:
	AIPatrol(class AIComponent* owner);

	// 이 상태에 대한 행위 재정의
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Patrol";
	}
};

class AIDeath :
	public AIState
{
public:
	AIDeath(class AIComponent* owner);

	// 이 상태에 대한 행위 재정의
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Death";
	}
};

class AIAttack :
	public AIState
{
public:
	AIAttack(class AIComponent* owner);

	// 이 상태에 대한 행위 재정의
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Attack";
	}
};

struct WeightedGraphEdge
{
	// 간선에 어떤 노드가 연결되어 있는가?
	WeightedGraphNode* mFrom;
	WeightedGraphNode* mTo;
	// 간선의 가중치
	float mWeight;
};

struct WeightedGraphNode
{
	// 외부로 향하는 간선들를 저장한다.
	std::vector<WeightedGraphEdge*> mEdges;
};