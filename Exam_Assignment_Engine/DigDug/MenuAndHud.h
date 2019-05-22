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
	void RemoveLife(bool playerOne = true);

private:
	int m_Score;
	int m_Lifes;
	int m_LifesPlayer2;
	bool m_TwoPlayers;

	dae::TextComponent* m_pTextComp;
	std::vector<dae::SpriteComponent*> m_pLifeSprites;
	std::vector<dae::SpriteComponent*> m_pLifeSpritesPlayer2;
};

