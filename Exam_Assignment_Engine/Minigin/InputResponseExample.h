#pragma once
#include "InputResponse.h"

class InputResponseExample final: public dae::InputResponse
{
public:
	InputResponseExample() = default;
	~InputResponseExample() = default;

	//override these 3 functions to handle the input with your custom actions
	virtual void ExecuteOnPress() override;
	virtual void ExecuteOnHold(const b2Vec2 axisValues) override;
	virtual void ExecuteOnRelease() override;
};

