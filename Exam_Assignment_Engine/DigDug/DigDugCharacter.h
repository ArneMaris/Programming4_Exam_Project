#pragma once
#include "Script.h"
#include "Components.h"

class DigDugCharacter : public dae::Script
{
public:
	DigDugCharacter();
	~DigDugCharacter();

	virtual void Initialize();
	virtual void Update();
	virtual void Render() const;
	virtual void PostRender() const;

private:
	dae::StateMachineComponent* m_pStateMachineComp;
};

