#include "pch.h"
#include "CollisionResponses.h"
#include "Logger.h"
#include "StateMachineComponent.h"
#include "AnimatedSpriteComponent.h"


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
	UNREFERENCED_PARAMETER(otherObj);
}

void EnemyCollision::OnCollisionEnd(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
}
