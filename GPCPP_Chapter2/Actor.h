#pragma once
#include <vector>
#include "Math.h"

class Actor
{
public:
	enum State
	{
		EActive, EPaused, EDead
	};
	// ������/�Ҹ���
	Actor(class Game* game);
	virtual ~Actor();
	// ���ӿ��� ȣ���ϴ� Update �Լ�
	void Update(float deltaTime);
	// ���Ϳ� ������ ��� ������Ʈ�� ������Ʈ
	void UpdateComponents(float deltaTime);
	// Ư�� ���Ϳ� Ưȭ�� Update �ڵ�
	virtual void UpdateActor(float deltaTime);

	// Getter/Setter
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }

	class Game* GetGame() { return mGame; }

	// ������Ʈ �߰�/����
	void AddCompoment(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// ������ ����
	State mState;
	// ��ȯ(Transform)
	Vector2 mPosition;	// ������ ����
	float mScale;		// ������ ����(100% = 1.0)
	float mRotation;	// ȸ�� ����(����)
	// �� ���Ͱ� ������ ������Ʈ��
	std::vector<class Component*> mComponents;
	class Game* mGame;
};