#pragma once
#include "AIComponent.h"

class AIState
{
public:
	AIState(AIComponent* owner)
		: mOwner(owner)
	{}
	// �� ������ ��ü���� �ൿ
	virtual void Update(float deltaTime) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	// ������ �̸� ���
	virtual const char* GetName() const = 0;

protected:
	AIComponent* mOwner;
};

class AIPatrol :
	public AIState
{
public:
	AIPatrol(class AIComponent* owner);

	// �� ���¿� ���� ���� ������
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

	// �� ���¿� ���� ���� ������
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

	// �� ���¿� ���� ���� ������
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
	// ������ � ��尡 ����Ǿ� �ִ°�?
	WeightedGraphNode* mFrom;
	WeightedGraphNode* mTo;
	// ������ ����ġ
	float mWeight;
};

struct WeightedGraphNode
{
	// �ܺη� ���ϴ� �����鸦 �����Ѵ�.
	std::vector<WeightedGraphEdge*> mEdges;
};