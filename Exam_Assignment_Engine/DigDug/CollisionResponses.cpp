#include "pch.h"
#include "CollisionResponses.h"
#include "Logger.h"
#include "StateMachineComponent.h"
#include "AnimatedSpriteComponent.h"

dae::GameObject* digDug = nullptr;

void DigDugCollision::OnCollisionStart(dae::GameObject * otherObj)
{
	if (otherObj->GetLayer() != 1)
		DontDoTransitionNow();

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
		return;
	}
	if (digDug == nullptr)
		digDug = dae::GetGameObjectByName(L"DigDugPump");

	if (otherObj == digDug)
	{
		dae::Logger::GetInstance().LogInfo(L"HIT Pump");
	}

	UNREFERENCED_PARAMETER(otherObj);
}

void EnemyCollision::OnCollisionEnd(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
}
