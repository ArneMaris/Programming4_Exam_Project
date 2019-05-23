#include "pch.h"
#include "PlayerFygarStates.h"
#include "AnimatedSpriteComponent.h"
#include "GameObject.h"
#include "Prefabs.h"


void PlayerFygarStates::PlayerFygarRun::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Run");
}

void PlayerFygarStates::PlayerFygarRun::OnStateExit()
{

}

void PlayerFygarStates::PlayerFygarRun::InState()
{

}

void PlayerFygarStates::PlayerFygarGhost::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Ghost");
}

void PlayerFygarStates::PlayerFygarGhost::OnStateExit()
{

}

void PlayerFygarStates::PlayerFygarGhost::InState()
{
}

void PlayerFygarStates::PlayerFygarAttacking::OnStateEnter()
{
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObjectRuntime(
		new FygarFlame(m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->GetFlipDirection(), m_pOwnerObject->GetTransform()->GetPosition()));
}

void PlayerFygarStates::PlayerFygarAttacking::OnStateExit()
{

}

void PlayerFygarStates::PlayerFygarAttacking::InState()
{

}
