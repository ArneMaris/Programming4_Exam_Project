#include "pch.h"
#include "MenuAndHud.h"
#include "ResourceManager.h"
#include "SceneManager.h"

MenuAndHud::MenuAndHud()
	:m_Score{0}
	,m_Lifes{3}
	,m_LifesPlayer2{3}
{

	if (dae::GetObjByNameActiveScene(L"DigDug2") != nullptr)
		m_TwoPlayers = true;
	else
		m_TwoPlayers = false;

	auto font = dae::ResourceManager::GetInstance().LoadFont("ConnectionSerif.otf", 35);

	auto texObj = new dae::GameObject();
	texObj->AddComponent(new dae::TextComponent(font, "SCORE", { 255,0,0 }));
	texObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth / 2), float(dae::GameInfo::windowHeight - 56));
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(texObj);

	//actuall score text (this one will be updated)
	texObj = new dae::GameObject();
	texObj->AddComponent(new dae::TextComponent(font, "0", { 240,240,240 }));
	texObj->GetComponent<dae::TextComponent>()->SetTextOffset({ 0,45 });
	texObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth / 2), float(dae::GameInfo::windowHeight - 88));
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(texObj);
	m_pTextComp = texObj->GetComponent<dae::TextComponent>();

	auto lifeObj = new dae::GameObject();
	lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
	lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
	lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
	lifeObj->GetTransform()->SetPosition(240, 60);
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(lifeObj);
	m_pLifeSprites = lifeObj->GetComponents<dae::SpriteComponent>();

	if (m_TwoPlayers)
	{
		lifeObj = new dae::GameObject();
		lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
		lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
		lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
		lifeObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth - 240), 60);
		dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(lifeObj);
		m_pLifeSpritesPlayer2 = lifeObj->GetComponents<dae::SpriteComponent>();
	}

	m_pSelectionObj = new dae::GameObject();
	m_pSelectionObj->AddComponent(new dae::SpriteComponent("MenuSelection.png"));
	m_pSelectionObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth /2 - 210), float(dae::GameInfo::windowHeight / 2 +50));
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(m_pSelectionObj);

	m_pMainMenuObj = new dae::GameObject();
	m_pMainMenuObj->AddComponent(new dae::SpriteComponent("StartMenu.png"));
	m_pMainMenuObj->SetRenderOrder(0);
	m_pMainMenuObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth / 2), float(dae::GameInfo::windowHeight / 2));
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(m_pMainMenuObj);

	m_pGameOverObj = new dae::GameObject();
	m_pGameOverObj->AddComponent(new dae::SpriteComponent("GameOverMenu.png"));
	m_pGameOverObj->SetRenderOrder(0);
	m_pGameOverObj->GetComponent<dae::SpriteComponent>()->SetDoRender(false);
	m_pGameOverObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth / 2), float(dae::GameInfo::windowHeight / 2));
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(m_pGameOverObj);
}


void MenuAndHud::Initialize()
{
	m_pTextComp->SetText(std::to_string(m_Score));
	float xOffset = 0;
	for (auto& spr : m_pLifeSprites)
	{
		spr->SetSpriteOffset({ xOffset,0 });
		spr->SetScale({ 2, 2 });
		spr->SetDoRender(true);
		xOffset += 35;
	}
}

void MenuAndHud::Update()
{

}

void MenuAndHud::Render() const
{

}

void MenuAndHud::PostRender() const
{

}

void MenuAndHud::AddScore(int score)
{
	m_Score += score;
	m_pTextComp->SetText(std::to_string(m_Score));
}

void MenuAndHud::RemoveLife(bool playerOne)
{
	if (playerOne)
	{
		--m_Lifes;
		if (m_Lifes == 0)
		{
			if (m_TwoPlayers)
			{
				if (m_LifesPlayer2 == 0)
				{
					//UR GAME OVER BITCH
				}
				else if (dae::GetObjByNameActiveScene(L"DigDug2") != nullptr)
				{
					dae::GetObjByNameActiveScene(L"DigDug2")->MarkForDelete();
				}
			}
			else
			{

				//UR GAME OVER BITCH
			}
		}
		else if (m_Lifes > -1)
		{
			m_pLifeSprites[m_Lifes]->SetDoRender(false);
		}
	}
	else
	{
		--m_LifesPlayer2;
		if (m_LifesPlayer2 == 0)
		{
			if (m_TwoPlayers)
			{
				if (m_Lifes == 0)
				{
					//UR GAME OVER BITCH
				}
				else
				{
					dae::GetObjByNameActiveScene(L"DigDug")->MarkForDelete();
				}
			}
			else 
			{

				//UR GAME OVER BITCH
			}
		}
		else if(m_LifesPlayer2 > -1)
		{
			m_pLifeSpritesPlayer2[m_LifesPlayer2]->SetDoRender(false);
		}
	}
}

void MenuAndHud::MoveDown()
{
}

void MenuAndHud::MoveUp()
{
}

void MenuAndHud::Enter()
{
}
