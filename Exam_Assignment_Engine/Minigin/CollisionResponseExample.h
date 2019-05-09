#pragma once
#include "CollisionResponse.h"
class CollisionResponseExample :public dae::CollisionResponse
{
public:
	CollisionResponseExample() = default;
	~CollisionResponseExample() = default;

	virtual void OnCollisionStart(dae::GameObject* otherObj) override;
	virtual void OnCollisionEnd(dae::GameObject* otherObj) override;
};

