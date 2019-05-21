#include "pch.h"
#include "CollisionResponses.h"
#include "Logger.h"
#include "StateMachineComponent.h"

void DigDugCollision::OnCollisionStart(dae::GameObject * otherObj)
{
	if (otherObj->GetLayer() != 1)
		DontDoTransitionNow();

	m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->TryTransitionToState(L"Run",L"Dead");
	m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->TryTransitionToState(L"Idle", L"Dead");
	UNREFERENCED_PARAMETER(otherObj);
}

void DigDugCollision::OnCollisionEnd(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
}



void EnemyCollision::OnCollisionStart(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
}

void EnemyCollision::OnCollisionEnd(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
}
