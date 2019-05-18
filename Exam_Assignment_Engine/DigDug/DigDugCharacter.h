#pragma once
#include "Script.h"
#include "Components.h"

class GameObject;
class DigDugCharacter : public dae::Script
{
public:
	DigDugCharacter();
	~DigDugCharacter();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() const override;
	virtual void PostRender() const override;

	void StartDigging();
	void EndDigging();

	float GetMoveSpeed() const { return m_MoveSpeed; };

private:
	dae::StateMachineComponent* m_pStateMachineComp;
	float m_MoveSpeed;
	bool m_Digging;
	dae::GameObject* m_DigObject;
};

