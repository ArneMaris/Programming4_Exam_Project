#pragma once
class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	virtual void ExecuteOnPress() = 0;
	virtual void ExecuteOnHold(const b2Vec2& axisValues) = 0;
	virtual void ExecuteOnRelease() = 0;

};

