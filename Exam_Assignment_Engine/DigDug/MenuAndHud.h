#pragma once
#include <Script.h>
#include "Components.h"

class MenuAndHud : public dae::Script
{
public:
	MenuAndHud();
	~MenuAndHud() = default;
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() const override;
	virtual void PostRender() const override;

	void AddScore(int score);
	void RemoveLife();

private:
	int m_Score;
	int m_Lifes;

	dae::TextComponent* m_pTextComp;
	std::vector<dae::SpriteComponent*> m_pLifeSprites;
};

