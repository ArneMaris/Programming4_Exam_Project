#include "MiniginPCH.h"
#include "TestScene.h"
#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "InputResponseExample.h"

TestScene::TestScene()
	:dae::Scene(L"TestScene")
{

}

void TestScene::Initialize()
{
	if (m_IsInitialized)
		return;

	//dae::Logger::EnableInterupOnError();
	//dae::Logger::GetInstance().LogError("testError");
	//dae::Logger::GetInstance().LogWarning("testWarning");
	dae::Logger::GetInstance().EnableInfoLogging();
	//dae::Logger::GetInstance().LogInfo("testInfo");


	 obj1 = new dae::GameObject();
	 obj2 = new dae::GameObject();

	obj1->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_dynamicBody));
	obj1->AddComponent(new dae::ColliderComponent(obj1->GetComponent<dae::PhysicsBodyComponent>()));
	obj1->GetComponent<dae::ColliderComponent>()->AddBoxShape(10, 10, dae::ShapeSettings(false, 1, 0.5f, 0));
	obj1->AddComponent(new dae::AnimatedSpriteComponent(L"SpriteTest.png", 4,2));
	obj1->GetTransform()->Translate(250, 500);
	AddGameObject(obj1);

	obj2->AddComponent(new dae::SpriteComponent(L"background.jpg"));
	obj2->GetTransform()->SetPosition(0,40);
	obj2->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_staticBody));
	obj2->AddComponent(new dae::ColliderComponent(obj2->GetComponent<dae::PhysicsBodyComponent>()));  //looks like it works
	obj2->GetComponent<dae::ColliderComponent>()->AddBoxShape(600, 20, dae::ShapeSettings(false, 1, 0.5f, 0));
	//obj2->GetComponent<dae::ColliderComponent>()->AddSVGCollision(L"Test.svg", true, dae::ShapeSettings(false, 1, 0.5f, 0));
	AddGameObject(obj2);

	obj1->GetComponent<dae::AnimatedSpriteComponent>()->AddAnimation({ L"RunLeft",0.1f, 0,1,0,2 });

	EnablePhysicsDebugDrawing();

	//auto font = dae::ResourceManager::GetInstance().LoadFont(L"Lingua.otf", 36);
	//obj = new dae::GameObject();
	//obj->SetPosition(80, 20);
	//obj->AddComponent(new dae::TextComponent(font, "Programming 4 Assignment"));
	//AddGameObject(obj);

	//obj = new dae::GameObject();
	//obj->AddComponent(new dae::FpsCounterComponent(font));
	//AddGameObject(obj);

	//obj = new dae::GameObject();
	//obj->SetPosition(20, 400);
	//obj->AddComponent(new dae::AnimatedSpriteComponent(L"SpriteTest.png", 4,2));
	//obj->GetComponent<dae::AnimatedSpriteComponent>()->SetSecondsPerFrame(0.5f);
	//obj->GetComponent<dae::AnimatedSpriteComponent>()->SetScale(4);
	//AddGameObject(obj);

	////testing the limits on the sprite to only play the sheet partially
	//obj = new dae::GameObject();
	//obj->SetPosition(80, 400);
	//obj->AddComponent(new dae::AnimatedSpriteComponent(L"SpriteTest.png", 4, 2));
	//obj->GetComponent<dae::AnimatedSpriteComponent>()->SetSecondsPerFrame(0.5f);
	//obj->GetComponent<dae::AnimatedSpriteComponent>()->SetScale(4);
	//obj->GetComponent<dae::AnimatedSpriteComponent>()->SetRowLimit(1, 1);
	////obj->GetComponent<dae::AnimatedSpriteComponent>()->SetColumnLimit(1, 2);
	//obj->GetComponent<dae::AnimatedSpriteComponent>()->SetColumnLimit(3, 4);
	//AddGameObject(obj);

	//dae::InputManager::GetInstance().AddInputAction(new InputResponseExample() , SDLK_w, dae::ControllerInput::DpadUp, 0);

	//dae::InputManager::GetInstance().AddInputAction(L"MoveRight", dae::ControllerInput::JoyStickLeft);
	////dae::InputManager::GetInstance().AddInputAction(L"MoveRight", dae::ControllerInput::DpadLeft);

	//dae::InputManager::GetInstance().AddInputAction(L"MoveLeft", dae::ControllerInput::DpadLeft);

	m_IsInitialized = true;
}

void TestScene::Update()
{


}

void TestScene::Render() const
{


}
