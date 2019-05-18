#include "pch.h"
#include "States.h"
#include "GameObject.h"
#include "Components.h"

void StateIdle::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetPaused(true);
}

void StateIdle::OnStateExit()
{

}

void StateIdle::InState()
{

}


void StateRunning::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetPaused(false);
}

void StateRunning::OnStateExit()
{

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
