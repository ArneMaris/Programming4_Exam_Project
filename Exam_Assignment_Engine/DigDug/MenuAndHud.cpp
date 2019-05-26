#include "pch.h"
#include "MenuAndHud.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "MenuInputResponses.h"

MenuAndHud::MenuAndHud()
	:m_Score{0}
	,m_Lifes{3}
	,m_LifesPlayer2{3}
	, m_PlayerOneDead{false}
	, m_PlayerTwoDead{false}
	, m_Versus{ false }
	, m_Ingame {false}
{
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
	for (auto& spriteComp : lifeObj->GetComponents<dae::SpriteComponent>())
		spriteComp->SetDoRender(false);
	lifeObj->GetTransform()->SetPosition(240, 60);
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(lifeObj);
	m_pLifeSprites = lifeObj->GetComponents<dae::SpriteComponent>();

	lifeObj = new dae::GameObject();
	lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
	lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
	lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
	for (auto& spriteComp : lifeObj->GetComponents<dae::SpriteComponent>())
		spriteComp->SetDoRender(false);
	lifeObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth - 240), 60);
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(lifeObj);
	m_pLifeSpritesPlayer2 = lifeObj->GetComponents<dae::SpriteComponent>();

	m_pSelectionObj = new dae::GameObject();
	m_pSelectionObj->AddComponent(new dae::SpriteComponent("MenuSelection.png"));
	m_pSelectionObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth /2 - 210), float(dae::GameInfo::windowHeight / 2 + 50));
	m_pSelectionObj->AddComponent(new dae::InputComponent(0, true));
	m_pSelectionObj->GetComponent<dae::InputComponent>()->AddInputAction(new MenuInput::KeyUp, SDLK_w, dae::ControllerInput::DpadUp);
	m_pSelectionObj->GetComponent<dae::InputComponent>()->AddInputAction(new MenuInput::KeyDown, SDLK_s, dae::ControllerInput::DpadDown);
	m_pSelectionObj->GetComponent<dae::InputComponent>()->AddInputAction(new MenuInput::Stick, dae::ControllerInput::JoyStickLeft);
	m_pSelectionObj->GetComponent<dae::InputComponent>()->AddInputAction(new MenuInput::Confirm, SDLK_SPACE, dae::ControllerInput::ButtonA);
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
		xOffset += 35;
	}
	xOffset = 0;
	for (auto& spr : m_pLifeSpritesPlayer2)
	{
		spr->SetSpriteOffset({ xOffset,0 });
		spr->SetScale({ 2, 2 });
		xOffset -= 35;
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
			m_pLifeSprites[0]->SetDoRender(false);
			if (m_TwoPlayers)
			{
				m_PlayerOneDead = true;

				//check if other was gameOver already, gameOver scene if yes
				if (m_PlayerTwoDead && m_LifesPlayer2 == 0)
				{
					dae::SceneManager::GetInstance().UnloadAllScenes();
					m_pGameOverObj->GetComponent<dae::SpriteComponent>()->SetDoRender(true);
				}
			}
			else
			{
				dae::SceneManager::GetInstance().UnloadAllScenes();
				m_pGameOverObj->GetComponent<dae::SpriteComponent>()->SetDoRender(true);
			}

		}
		else
			//it will only get here if there are 2 players ofcourse (function will otherwise never be called with parameter = false)
		{
			m_pLifeSprites[m_Lifes]->SetDoRender(false);

			if (m_TwoPlayers)
			{
				m_PlayerOneDead = true;

				//check if other was dead already, reload scene if yes
				if (m_PlayerTwoDead)
				{
					dae::SceneManager::GetInstance().ReloadActiveScene();
					m_PlayerTwoDead = false;
					m_PlayerOneDead = false;
				}
				else
				{
					for (auto& obj : dae::GetAllObjsInLayerActiveScene(1))
					{
						if (obj->GetComponent<dae::AiComponent>())
						{
							obj->GetComponent<dae::AiComponent>()->SetNewTarget(dae::GetObjByNameActiveScene(L"DigDug2"));
						}
					}
				}

			}
			else
			{
				dae::SceneManager::GetInstance().ReloadActiveScene();
			}
		}

	}
	else
	{
		--m_LifesPlayer2;
		if (m_LifesPlayer2 == 0)
		{
			m_pLifeSpritesPlayer2[0]->SetDoRender(false);
			m_PlayerTwoDead = true;

			//check if other was gameOver already, gameOver scene if yes
			if (m_PlayerOneDead && m_Lifes == 0)
			{
				dae::SceneManager::GetInstance().UnloadAllScenes();
				m_pGameOverObj->GetComponent<dae::SpriteComponent>()->SetDoRender(true);
			}
		}
		else
		{
			m_pLifeSpritesPlayer2[m_LifesPlayer2]->SetDoRender(false);
			m_PlayerTwoDead = true;

			//check if other was dead already, reload scene if yes
			if (m_PlayerOneDead)
			{
				dae::SceneManager::GetInstance().ReloadActiveScene();
				m_PlayerTwoDead = false;
				m_PlayerOneDead = false;
			}
			else
			{
				for (auto& obj : dae::GetAllObjsInLayerActiveScene(1))
				{
					if (obj->GetComponent<dae::AiComponent>())
					{
						obj->GetComponent<dae::AiComponent>()->SetNewTarget(dae::GetObjByNameActiveScene(L"DigDug"));
					}
				}
			}
		}
	}
}

void MenuAndHud::MoveDown()
{
	switch (m_CurrentMode)
	{
	case MenuAndHud::single:
		m_pSelectionObj->GetTransform()->Translate({ 0,-53 });
		m_CurrentMode = coop;
		break;
	case MenuAndHud::coop:
		m_pSelectionObj->GetTransform()->Translate({ 0,-53 });
		m_CurrentMode = versus;
		break;
	}
}

void MenuAndHud::MoveUp()
{
	switch (m_CurrentMode)
	{
	case MenuAndHud::coop:
		m_pSelectionObj->GetTransform()->Translate({ 0,53 });
		m_CurrentMode = single;
		break;
	case MenuAndHud::versus:
		m_pSelectionObj->GetTransform()->Translate({ 0,53 });
		m_CurrentMode = coop;
		break;
	}
}

void MenuAndHud::Confirm()
{
	m_Ingame = true;
	m_TwoPlayers = false;
	m_Versus = false;
	m_PlayerTwoDead = false;
	m_PlayerOneDead = false;
	m_pSelectionObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth / 2 - 210), float(dae::GameInfo::windowHeight / 2 + 50));
	switch (m_CurrentMode)
	{
	case MenuAndHud::coop:
		m_TwoPlayers = true;
		m_LifesPlayer2 = 3;
		for (auto& sprite : m_pLifeSpritesPlayer2)
		{
			sprite->SetDoRender(true);
		}
	case MenuAndHud::single:
		m_pMainMenuObj->GetComponent<dae::SpriteComponent>()->SetDoRender(false);
		m_CurrentMode = back;
		m_Lifes = 3;
		for (auto& sprite : m_pLifeSprites)
		{
			sprite->SetDoRender(true);
		}
		dae::SceneManager::GetInstance().SetActiveScene(L"DigDugLevel1");
		break;
	case MenuAndHud::versus:
		m_pMainMenuObj->GetComponent<dae::SpriteComponent>()->SetDoRender(false);
		m_CurrentMode = back;
		m_Lifes = 3;
		m_Versus = true;
		for (auto& sprite : m_pLifeSprites)
		{
			sprite->SetDoRender(true);
		}
		dae::SceneManager::GetInstance().SetActiveScene(L"DigDugLevel1");
		break;
	case MenuAndHud::back:
		m_CurrentMode = single;
		m_pSelectionObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth / 2 - 210), float(dae::GameInfo::windowHeight / 2 + 50));
		m_pMainMenuObj->GetComponent<dae::SpriteComponent>()->SetDoRender(true);
		m_pGameOverObj->GetComponent<dae::SpriteComponent>()->SetDoRender(false);
		m_Ingame = false;
		break;
	}

	
}
