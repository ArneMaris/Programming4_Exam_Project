#pragma once
#include "InputResponse.h"


class PlayerFygarAttack final : public dae::InputResponse
{
public:
	PlayerFygarAttack() = default;
	~PlayerFygarAttack() = default;

	//override these 3 functions to handle the input with your custom actions
	virtual void ExecuteOnPress() override;
	virtual void ExecuteOnRelease() override;
};

class PlayerFygarMove final : public dae::InputResponse
{
public:
	PlayerFygarMove() = default;
	~PlayerFygarMove() = default;

	//override these 3 functions to handle the input with your custom actions
	virtual void ExecuteOnPress() override;
	virtual void ExecuteOnHold(const b2Vec2 axisValues) override;
	virtual void ExecuteOnRelease() override;
};

