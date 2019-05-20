#include "pch.h"
#include "CollisionResponses.h"
#include "Logger.h"


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
	UNREFERENCED_PARAMETER(otherObj);
}

void EnemyCollision::OnCollisionEnd(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
}
