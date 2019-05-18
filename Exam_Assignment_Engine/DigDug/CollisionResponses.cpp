#include "pch.h"
#include "CollisionResponses.h"
#include "Logger.h"


void DigDugCollision::OnCollisionStart(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
	dae::Logger::GetInstance().LogInfo(L"collision detected!");
}

void DigDugCollision::OnCollisionEnd(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
}




void CollisionResponseExample2::OnCollisionStart(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
	dae::Logger::GetInstance().LogInfo(L"collision detected2!");
}

void CollisionResponseExample2::OnCollisionEnd(dae::GameObject * otherObj)
{
	UNREFERENCED_PARAMETER(otherObj);
}
