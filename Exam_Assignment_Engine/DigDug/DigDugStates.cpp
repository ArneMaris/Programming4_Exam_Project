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
}

void DigDugStates::Dead::OnStateExit()
{
}

void DigDugStates::Dead::InState()
{
}

void DigDugStates::Dragged::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Dragged");
}

void DigDugStates::Dragged::OnStateExit()
{
}

void DigDugStates::Dragged::InState()
{
	auto newHeight = m_pOwnerObject->GetTransform()->GetPosition().y;
	if (!(newHeight < m_Height))
	{
		m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->SetToState(L"Squashed");
	}
}

void DigDugStates::Squashed::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"DieStone");
	m_pOwnerObject->GetComponent<dae::InputComponent>()->DisableInput();
}

void DigDugStates::Squashed::OnStateExit()
{
}

void DigDugStates::Squashed::InState()
{
}

