#pragma once
#include "CollisionResponse.h"
#include "GameObject.h"

class DigDugCollision :public dae::CollisionResponse
{
public:
	DigDugCollision() = default;
	~DigDugCollision() = default;

	virtual void OnCollisionStart(dae::GameObject* otherObj) override;
	virtual void OnCollisionEnd(dae::GameObject* otherObj) override;
};

class CollisionResponseExample2 :public dae::CollisionResponse
{
public:
	CollisionResponseExample2() = default;
	~CollisionResponseExample2() = default;

	virtual void OnCollisionStart(dae::GameObject* otherObj) override;
	virtual void OnCollisionEnd(dae::GameObject* otherObj) override;
};

