#pragma once
#include "Game.h"

class Component
{
public:
	// 생성자 (업데이트 순서 값이 작을수록 빨리 업데이트 됨.)
	Component(class Actor* owner, int updateOrder = 100);
	// 소멸자
	virtual ~Component();
	// 델타 시간으로 이 컴포넌트를 업데이트
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// 소유자 액터
	class Actor* mOwner;
	// 컴포넌트의 업데이트 순서
	int mUpdateOrder;
};