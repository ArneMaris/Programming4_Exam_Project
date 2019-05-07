#pragma once
class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	virtual void ExecuteOnPress() = 0;
	virtual void ExecuteOnHold() = 0;
	virtual void ExecuteOnRelease() = 0;

};

