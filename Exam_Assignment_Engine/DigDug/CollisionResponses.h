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

class EnemyCollision :public dae::CollisionResponse
{
public:
	EnemyCollision() = default;
	~EnemyCollision() = default;

	virtual void OnCollisionStart(dae::GameObject* otherObj) override;
	virtual void OnCollisionEnd(dae::GameObject* otherObj) override;
};

class PumpCollision :public dae::CollisionResponse
{
public:
	PumpCollision() = default;
	~PumpCollision() = default;

	virtual void OnCollisionStart(dae::GameObject* otherObj) override;
	virtual void OnCollisionEnd(dae::GameObject* otherObj) override;
};

