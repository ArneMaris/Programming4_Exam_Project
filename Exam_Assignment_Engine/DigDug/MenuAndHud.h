#pragma once
#include <Script.h>
#include "Components.h"

class MenuAndHud : public dae::Script
{
public:
	enum Mode
	{
		single,
		coop,
		versus,
		retry,
		exit
	};

	MenuAndHud();
	~MenuAndHud() = default;
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() const override;
	virtual void PostRender() const override;

	void AddScore(int score);
	void RemoveLife(bool playerOne = true);

	void MoveDown();
	void MoveUp();
	void Confirm();

	bool GetIsTwoPlayers() const { return m_TwoPlayers; };

private:
	int m_Score;
	int m_Lifes;
	int m_LifesPlayer2;
	bool m_TwoPlayers;

	bool m_Ingame;

	dae::TextComponent* m_pTextComp;
	std::vector<dae::SpriteComponent*> m_pLifeSprites;
	std::vector<dae::SpriteComponent*> m_pLifeSpritesPlayer2;

	dae::GameObject* m_pSelectionObj;
	dae::GameObject* m_pMainMenuObj;
	dae::GameObject* m_pGameOverObj;

	Mode m_CurrentMode;
};

