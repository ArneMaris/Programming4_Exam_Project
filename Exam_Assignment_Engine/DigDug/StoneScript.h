#pragma once
#include <Script.h>
#include "GridTile.h"
class StoneScript : public dae::Script
{
public:
	StoneScript();
	~StoneScript() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() const override;
	virtual void PostRender() const override;

	bool GetIsFalling() const { return m_IsFalling; };
private:
	bool m_IsFalling;
	bool m_Losening;
	float m_LosenDuration;
	float m_LosenTimer;
	float m_FallingSpeed;
	dae::GridTile* m_TileUnder;
	dae::GridLevel* m_Level;
};

