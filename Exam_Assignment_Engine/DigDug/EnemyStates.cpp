#include "pch.h"
#include "EnemyStates.h"
#include "GameObject.h"
#include "Components.h"
#include "SceneManager.h"
#include "GridLevel.h"
#include "Prefabs.h"
#include "MenuAndHud.h"

void EnemyStates::Run::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Run");
	m_pOwnerObject->GetComponent<dae::AiComponent>()->SetActive(true);
}

void EnemyStates::Run::OnStateExit()
{

}

void EnemyStates::Run::InState()
{
	//was more to the left means is running right now
	if (m_PrevXPos < m_pOwnerObject->GetTransform()->GetPosition().x)
		m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetFlipDirection(SDL_FLIP_NONE);
	else
		m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetFlipDirection(SDL_FLIP_HORIZONTAL);

	m_PrevXPos = m_pOwnerObject->GetTransform()->GetPosition().x;

	if (m_pOwnerObject->GetComponent<dae::AiComponent>()->GetCanReachGoal() == false && m_pOwnerObject->GetComponent<dae::AiComponent>()->IsActive())
	{
		if (rand() % 300 == 0)
			m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->SetToState(L"Ghost");
	}
	else if (rand() % 1500 == 0)
	{
		m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->SetToState(L"Ghost");
	}

	if (rand() % 400 == 0 && m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->GetCurrentStateName() == L"Run")
	{
		//this will only work on the fygars (intented)
		if (m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"FygarAttack"))
			m_pOwnerObject->GetComponent<dae::AiComponent>()->SetActive(false);
	}

}

void EnemyStates::Ghost::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AiComponent>()->SetActive(false);
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Ghost");
	auto tile = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1]->GetWalkableTileInRadius(m_pOwnerObject->GetTransform()->GetPosition(), 3, 500);
	if (tile != nullptr)
		m_pOwnerObject->GetTransform()->MoveToPosition(tile->GetPos(),m_pOwnerObject->GetComponent<dae::AiComponent>()->GetSpeed(), false, true);
	else
	{
		m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->SetToState(L"Run");
	}
}

void EnemyStates::Ghost::OnStateExit()
{

}

void EnemyStates::Ghost::InState()
{
	if (!m_pOwnerObject->GetTransform()->GetIsMovingToAPos())
	{
		m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->SetToState(L"Run");
	}
}

void EnemyStates::BlowUpOne::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"BlowUpOne");
}

void EnemyStates::BlowUpOne::OnStateExit()
{

}

void EnemyStates::BlowUpOne::InState()
{

}

void EnemyStates::BlowUpTwo::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"BlowUpTwo");
}

void EnemyStates::BlowUpTwo::OnStateExit()
{

}

void EnemyStates::BlowUpTwo::InState()
{

}

void EnemyStates::BlowUpThree::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"BlowUpThree");
}

void EnemyStates::BlowUpThree::OnStateExit()
{

}

void EnemyStates::BlowUpThree::InState()
{

}

void EnemyStates::Pop::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Pop");
	auto tile = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[0]->GetTileByPos(m_pOwnerObject->GetTransform()->GetPosition());
	auto texName = tile->GetTextureName();
	//determine layer by textureName
	auto menuHudScript = static_cast<MenuAndHud*>(dae::GetObjByNameGlobalScene(L"MenuHud")->GetComponent<dae::ScriptComponent>()->GetScript());

	bool killedFygarHorizontal = false;
	if (m_pOwnerObject->GetName() == L"Fygar")
	{
		auto digDug1 = dae::GetObjByNameActiveScene(L"DigDug");
		auto digDug2 = dae::GetObjByNameActiveScene(L"DigDug2");
		dae::GameObject* killerDigDug = nullptr;
		if (digDug2 != nullptr)
		{
			float dist1 = b2Distance(digDug1->GetTransform()->GetPosition(), m_pOwnerObject->GetTransform()->GetPosition());
			float dist2 = b2Distance(digDug2->GetTransform()->GetPosition(), m_pOwnerObject->GetTransform()->GetPosition());
			if (dist1 < dist2)
				killerDigDug = digDug1;
			else
				killerDigDug = digDug2;
		}
		else
		{
			killerDigDug = digDug1;
		}

		if (m_pOwnerObject->GetTransform()->GetPosition().y < killerDigDug->GetTransform()->GetPosition().y + 20
				&& m_pOwnerObject->GetTransform()->GetPosition().y > killerDigDug->GetTransform()->GetPosition().y - 20)
			killedFygarHorizontal = true;
	}

	if (texName == "Tiles/Layer1.png")
	{
		if (m_pOwnerObject->GetName() == L"Pooka")
			menuHudScript->AddScore(200);
		else if (m_pOwnerObject->GetName() == L"Fygar")
			if (killedFygarHorizontal)
				menuHudScript->AddScore(800);
			else
				menuHudScript->AddScore(400);
	}
	else if (texName == "Tiles/Layer2.png")
	{
		if (m_pOwnerObject->GetName() == L"Pooka")
			menuHudScript->AddScore(300);
		else if (m_pOwnerObject->GetName() == L"Fygar")
			if (killedFygarHorizontal)
				menuHudScript->AddScore(1200);
			else
				menuHudScript->AddScore(600);
	}
	else if (texName == "Tiles/Layer3.png")
	{
		if (m_pOwnerObject->GetName() == L"Pooka")
			menuHudScript->AddScore(400);
		else if (m_pOwnerObject->GetName() == L"Fygar")
			if (killedFygarHorizontal)
				menuHudScript->AddScore(1600);
			else
				menuHudScript->AddScore(800);
	}
	else if (texName == "Tiles/Layer4.png")
	{
		if (m_pOwnerObject->GetName() == L"Pooka")
			menuHudScript->AddScore(500);
		else if (m_pOwnerObject->GetName() == L"Fygar")
			if (killedFygarHorizontal)
				menuHudScript->AddScore(2000);
			else
				menuHudScript->AddScore(1000);
	}
	m_pOwnerObject->SetLifeTime(1.5f);
}

void EnemyStates::Pop::OnStateExit()
{

}

void EnemyStates::Pop::InState()
{

}

void EnemyStates::Attacking::OnStateEnter()
{
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObjectRuntime(
		new FygarFlame(m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->GetFlipDirection()), m_pOwnerObject->GetTransform()->GetPosition());
	m_pOwnerObject->GetComponent<dae::AiComponent>()->SetActive(false);
}

void EnemyStates::Attacking::OnStateExit()
{

}

void EnemyStates::Attacking::InState()
{
	
}