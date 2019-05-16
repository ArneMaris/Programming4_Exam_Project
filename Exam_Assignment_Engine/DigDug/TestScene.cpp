#include "pch.h"
#include "TestScene.h"
#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameInfo.h"
#include "Prefabs.h"
#include "GridLevel.h"
#include "StateTransition.h"

TestScene::TestScene()
	:dae::Scene(L"TestScene")
{
}

void TestScene::Initialize()
{
	if (m_IsInitialized)
		return;

	dae::Logger::GetInstance().EnableInfoLogging();

	AddGameObject(new DigDug());

	m_pActiveLevel = new dae::GridLevel(L"Level1.txt", { 0,0 });

	//add the prefab's gameObject to the scene, destroy prefab after


	EnablePhysicsDebugDrawing();

	m_IsInitialized = true;
}

void TestScene::Update()
{


}

void TestScene::Render() const
{


}
