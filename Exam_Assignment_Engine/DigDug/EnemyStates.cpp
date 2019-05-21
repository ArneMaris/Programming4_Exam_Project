#include "pch.h"
#include "EnemyStates.h"
#include "GameObject.h"
#include "Components.h"
#include "SceneManager.h"
#include "GridLevel.h"

void EnemyStates::Run::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Run");
}

void EnemyStates::Run::OnStateExit()
{
}

void EnemyStates::Run::InState()
{
	if (m_pOwnerObject->GetComponent<dae::AiComponent>()->GetCanReachGoal() == false)
	{
		if (rand() % 100 == 0)
			m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->SetToState(L"Ghost");
	}
	else if (rand() % 500 == 0)
	{
		m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->SetToState(L"Ghost");
	}

}

void EnemyStates::Ghost::OnStateEnter()
{
	m_pOwnerObject->GetComponent<dae::AiComponent>()->SetActive(false);
	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Ghost");
	auto tile = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1]->GetWalkableTileInRadius(m_pOwnerObject->GetTransform()->GetPosition(), 3, 500);
	if (tile != nullptr)
		m_pOwnerObject->GetTransform()->MoveToPosition(tile->GetPos(),m_pOwnerObject->GetComponent<dae::AiComponent>()->GetSpeed(), false, true);
}

void EnemyStates::Ghost::OnStateExit()
{
}

void EnemyStates::Ghost::InState()
{
	if (!m_pOwnerObject->GetTransform()->GetIsMovingToAPos())
	{
		m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->SetToState(L"Run");
		m_pOwnerObject->GetComponent<dae::AiComponent>()->SetActive(true);
	}
}

void EnemyStates::BlowUpOne::OnStateEnter()
{
}

void EnemyStates::BlowUpOne::OnStateExit()
{
}

void EnemyStates::BlowUpOne::InState()
{
}

void EnemyStates::BlowUpTwo::OnStateEnter()
{
}

void EnemyStates::BlowUpTwo::OnStateExit()
{
}

void EnemyStates::BlowUpTwo::InState()
{
}

void EnemyStates::BlowUpThree::OnStateEnter()
{
}

void EnemyStates::BlowUpThree::OnStateExit()
{
}

void EnemyStates::BlowUpThree::InState()
{
}

void EnemyStates::Pop::OnStateEnter()
{
}

void EnemyStates::Pop::OnStateExit()
{
}

void EnemyStates::Pop::InState()
{
}
