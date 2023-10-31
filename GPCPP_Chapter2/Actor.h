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
	// 생성자/소멸자
	Actor(class Game* game);
	virtual ~Actor();
	// 게임에서 호출하는 Update 함수
	void Update(float deltaTime);
	// 액터에 부착된 모든 컴포넌트를 업데이트
	void UpdateComponents(float deltaTime);
	// 특정 액터에 특화된 Update 코드
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

	// 컴포넌트 추가/제거
	void AddCompoment(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// 액터의 상태
	State mState;
	// 변환(Transform)
	Vector2 mPosition;	// 액터의 중점
	float mScale;		// 액터의 배율(100% = 1.0)
	float mRotation;	// 회전 각도(라디안)
	// 이 액터가 보유한 컴포넌트들
	std::vector<class Component*> mComponents;
	class Game* mGame;
};