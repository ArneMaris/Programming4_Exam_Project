#include "pch.h"
#include "States.h"
#include "GameObject.h"
#include "Components.h"
#include "DigDugCharacter.h"

void StateIdle::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetPaused(true);
}

void StateIdle::OnStateExit()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetPaused(false);
}

void StateIdle::InState()
{

}

void StateRunning::OnStateEnter()
{
	static_cast<DigDugCharacter*>(m_pOwnerObject->GetScript())->StartDigging();
}

void StateRunning::OnStateExit()
{
	static_cast<DigDugCharacter*>(m_pOwnerObject->GetScript())->EndDigging();
}

void StateRunning::InState()
{

}


void StateDead::OnStateEnter()
{

}

void StateDead::OnStateExit()
{
}

void StateDead::InState()
{
}
