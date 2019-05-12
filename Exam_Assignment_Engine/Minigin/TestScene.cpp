#include "MiniginPCH.h"
#include "TestScene.h"
#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "MoveUp.h"
#include "CollisionResponseExample.h"
#include "GameInfo.h"
#include "ExamplePrefab.h"
#include "GridLevel.h"
#include "StatesExample.h"
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

	obj1 = new dae::GameObject();

	obj1->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_dynamicBody));
	obj1->AddComponent(new dae::ColliderComponent(obj1->GetComponent<dae::PhysicsBodyComponent>()));
	obj1->GetComponent<dae::ColliderComponent>()->AddBoxShape(10, 10, dae::ShapeSettings(false, 1, 0.5f, 0));
	obj1->AddComponent(new dae::AnimatedSpriteComponent(L"SpriteTest.png", 4,2));
	obj1->GetTransform()->Translate(250, 500);
	obj1->AddComponent(new dae::InputComponent(-1, true));

	auto moveUpCommand = new MoveUp();
	obj1->GetComponent<dae::InputComponent>()->AddInputAction(moveUpCommand, SDLK_w);

	obj1->GetComponent<dae::AnimatedSpriteComponent>()->AddAnimation({ L"RunLeft",0.1f, 0,1,0,2 });

	auto collResp = new CollisionResponseExample2;
	obj1->GetComponent<dae::ColliderComponent>()->AddCollisionResponse(collResp);
	obj1->AddComponent(new dae::StateMachineComponent());


	auto sm = obj1->GetComponent<dae::StateMachineComponent>();
	sm->AddState(L"Idle", new StateIdle(), true);
	sm->AddState(L"Running", new StateRunning(), false);
	sm->AddState(L"Dead", new StateDead(), false);
	sm->AddStateToStateTransition(L"Idle", L"Running", moveUpCommand, true); //add trans from idle to run when MoveUpCommand is pressed
	sm->AddStateToStateTransition(L"Running", L"Idle", moveUpCommand, false); //add trans from run to idle when MoveUpCommand is released
	sm->AddToStateTransition(L"Dead", collResp, true);
	AddGameObject(obj1);

	AddGameObject(new ExamplePrefab());

	//new dae::GridLevel(L"Level1.txt", 0);

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
