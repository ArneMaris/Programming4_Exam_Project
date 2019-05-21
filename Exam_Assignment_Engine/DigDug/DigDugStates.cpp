#include "pch.h"
#include "DigDugStates.h"
#include "GameObject.h"
#include "Components.h"
#include "DigDugCharacter.h"
#include "SceneManager.h"

void DigDugStates::Idle::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Idle");
}

void DigDugStates::Idle::OnStateExit()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"RunWeapon");
}

void DigDugStates::Idle::InState()
{

}

void DigDugStates::Run::OnStateEnter()
{
	static_cast<DigDugCharacter*>(m_pOwnerObject->GetScript())->StartDigging();
}

void DigDugStates::Run::OnStateExit()
{
	static_cast<DigDugCharacter*>(m_pOwnerObject->GetScript())->EndDigging();
}

void DigDugStates::Run::InState()
{

}

void DigDugStates::Dead::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"DieEnemy");
	m_pOwnerObject->GetComponent<dae::InputComponent>()->DisableInput();
	
	for (auto& enemy : dae::GetAllGameObjectsInLayer(1))
	{
		enemy->GetComponent<dae::AiComponent>()->SetActive(false);
	}

	std::function<void()> func = std::bind(&dae::SceneManager::ReloadActiveScene, &dae::SceneManager::GetInstance());
	dae::CallFunctionAfter(func, 5000);
}

void DigDugStates::Dead::OnStateExit()
{
}

void DigDugStates::Dead::InState()
{
}
