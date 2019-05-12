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

	obj1->GetComponent<dae::InputComponent>()->AddInputAction(new MoveUp(), SDLK_w);

	obj1->GetComponent<dae::AnimatedSpriteComponent>()->AddAnimation({ L"RunLeft",0.1f, 0,1,0,2 });
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
