#include "pch.h"
#include "CollisionResponses.h"
#include "Logger.h"
#include "Components.h"
#include "DigDugCharacter.h"
#include "StoneScript.h"


void DigDugCollision::OnCollisionStart(dae::GameObject * otherObj)
{
	//layer 1 is enemies layer
	if (otherObj->GetLayer() != 1)
	{
		DontDoTransitionNow();
	}

	if (otherObj->GetLayer() == 3) //layer 3 is a stone
	{
		if (static_cast<StoneScript*>(otherObj->GetComponent<dae::ScriptComponent>()->GetScript())->GetIsFalling())
		{
			if (m_pOwnerObject->GetTransform()->GetPosition().y < otherObj->GetTransform()->GetPosition().y)
				m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->SetToState(L"Dragged");
		}
	}

	UNREFERENCED_PARAMETER(otherObj);
}

void DigDugCollision::OnCollisionEnd(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
}


void EnemyCollision::OnCollisionStart(dae::GameObject * otherObj)
{
	//layer 2 is pump's layer
	if (otherObj->GetLayer() != 2)
	{
		DontDoTransitionNow();	
	}
	if (otherObj->GetLayer() == 3) //layer 3 is a stone
	{
		if (static_cast<StoneScript*>(otherObj->GetComponent<dae::ScriptComponent>()->GetScript())->GetIsFalling())
		{
			if (m_pOwnerObject->GetTransform()->GetPosition().y < otherObj->GetTransform()->GetPosition().y)
				m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->SetToState(L"Dragged");
		}
	}
	
	UNREFERENCED_PARAMETER(otherObj);
}

void EnemyCollision::OnCollisionEnd(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
}

void PumpCollision::OnCollisionStart(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
	if (otherObj->GetLayer() == 1)
		m_pOwnerObject->GetComponent<dae::ColliderComponent>()->SetActive(false);
}

void PumpCollision::OnCollisionEnd(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
}
