#pragma once
#include "InputResponse.h"

class MoveController final: public dae::InputResponse
{
public:
	MoveController() = default;
	~MoveController() = default;

	//override these 3 functions to handle the input with your custom actions
	virtual void ExecuteOnPress() override;
	virtual void ExecuteOnHold(const b2Vec2 axisValues) override;
	virtual void ExecuteOnRelease() override;
};

class MoveUpKey final : public dae::InputResponse
{
public:
	MoveUpKey() = default;
	~MoveUpKey() = default;

	//override these 3 functions to handle the input with your custom actions
	virtual void ExecuteOnPress() override;
	virtual void ExecuteOnHold(const b2Vec2 axisValues) override;
	virtual void ExecuteOnRelease() override;
};

class MoveDownKey final : public dae::InputResponse
{
public:
	MoveDownKey() = default;
	~MoveDownKey() = default;

	//override these 3 functions to handle the input with your custom actions
	virtual void ExecuteOnPress() override;
	virtual void ExecuteOnHold(const b2Vec2 axisValues) override;
	virtual void ExecuteOnRelease() override;
};

class MoveLeftKey final : public dae::InputResponse
{
public:
	MoveLeftKey() = default;
	~MoveLeftKey() = default;

	//override these 3 functions to handle the input with your custom actions
	virtual void ExecuteOnPress() override;
	virtual void ExecuteOnHold(const b2Vec2 axisValues) override;
	virtual void ExecuteOnRelease() override;
};

class MoveRightKey final : public dae::InputResponse
{
public:
	MoveRightKey() = default;
	~MoveRightKey() = default;

	//override these 3 functions to handle the input with your custom actions
	virtual void ExecuteOnPress() override;
	virtual void ExecuteOnHold(const b2Vec2 axisValues) override;
	virtual void ExecuteOnRelease() override;
};

