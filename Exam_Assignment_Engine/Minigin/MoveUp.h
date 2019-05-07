#pragma once
#include "Command.h"
class MoveUp :
	public Command
{
public:
	MoveUp() = default;
	~MoveUp() = default;

	//override these 3 functions to handle the input with your custom actions
	virtual void ExecuteOnPress() override;
	virtual void ExecuteOnHold() override;
	virtual void ExecuteOnRelease() override;
};

