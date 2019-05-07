#pragma once
#include "Command.h"

class CommandExample final: public Command
{
public:
	CommandExample() = default;
	~CommandExample() = default;

	//override these 3 functions to handle the input with your custom actions
	virtual void ExecuteOnPress() override;
	virtual void ExecuteOnHold(const b2Vec2& axisValues) override;
	virtual void ExecuteOnRelease() override;
};

