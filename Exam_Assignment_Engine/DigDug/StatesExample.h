#pragma once
#include "State.h"

class StateIdle : public dae::State
{
public:
	StateIdle() = default;
	~StateIdle() = default;

	virtual void OnStateEnter() override;
	virtual void OnStateExit() override;
	virtual void InState() override;
};

class StateRunning : public dae::State
{
public:
	StateRunning() = default;
	~StateRunning() = default;

	virtual void OnStateEnter() override;
	virtual void OnStateExit() override;
	virtual void InState() override;
};

class StateDead : public dae::State
{
public:
	StateDead() = default;
	~StateDead() = default;

	virtual void OnStateEnter() override;
	virtual void OnStateExit() override;
	virtual void InState() override;
};