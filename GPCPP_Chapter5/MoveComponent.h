#pragma once
#include "Component.h"
class MoveComponent :
    public Component
{
public:
    MoveComponent(class Actor* owner, int updateOrder = 10);

    void Update(float deltaTime) override;

    //Getters and Setters
    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
    float GetAngularSpeed() const { return mAngularSpeed; }
    float GetForwardSpeed() const { return mForwardSpeed; }

private:
    // 회전을 제어(초당 라디안)
    float mAngularSpeed;
    // 전방 이동을 제어(초당 단위)
    float mForwardSpeed;
};

