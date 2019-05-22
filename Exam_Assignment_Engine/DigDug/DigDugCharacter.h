#pragma once
#include "Script.h"
#include "Components.h"
#include "GridTile.h"

class GameObject;
class GridLevel;

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

	void Pump();

	float GetMoveSpeed() const { return m_MoveSpeed; };

private:
	dae::StateMachineComponent* m_pStateMachineComp;
	float m_MoveSpeed;
	bool m_Digging;
	dae::GameObject* m_DigObject;
	dae::GameObject* m_PumpObject;
	dae::GridLevel* m_pLevel;
	dae::GridTile* m_PrevTile;

	b2Vec2 m_StartPos;

	float m_DeadTimer;
	float m_PumpFlySpeed;
	b2Vec2 m_PumpForce;
	bool m_Pumping;
};

