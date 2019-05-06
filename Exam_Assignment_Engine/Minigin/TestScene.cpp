#include "MiniginPCH.h"
#include "TestScene.h"
#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "InputAction.h"

TestScene::TestScene()
	:dae::Scene(L"TestScene")
{

}

void TestScene::Initialize()
{
	if (m_IsInitialized)
		return;

	//dae::Logger::EnableInterupOnError();
	//dae::Logger::LogError("testError");
	//dae::Logger::LogWarning("testWarning");
	dae::Logger::EnableInfoLogging();
	//dae::Logger::LogInfo("testInfo");


	 obj1 = new dae::GameObject();
	 obj2 = new dae::GameObject();

	obj1->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_dynamicBody));
	obj1->AddComponent(new dae::ColliderComponent(obj1->GetComponent<dae::PhysicsBodyComponent>()));
	obj1->GetComponent<dae::ColliderComponent>()->AddBoxShape(10, 10, dae::ShapeSettings(false, 1, 0.5f, 0));
	obj1->AddComponent(new dae::AnimatedSpriteComponent(L"SpriteTest.png", 4,2));
	obj1->GetTransform()->Translate(20, 60);
	AddGameObject(obj1);

	obj2->AddComponent(new dae::SpriteComponent(L"background.jpg"));
	obj2->GetTransform()->SetPosition(0,40);
	obj2->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_staticBody));
	obj2->AddComponent(new dae::ColliderComponent(obj2->GetComponent<dae::PhysicsBodyComponent>()));
	obj2->GetComponent<dae::ColliderComponent>()->AddBoxShape(600, 20, dae::ShapeSettings(false, 1, 0.5f, 0));
	AddGameObject(obj2);

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

	//dae::InputManager::GetInstance().AddInputAction(L"MoveUp", SDL_SCANCODE_W, dae::ControllerInput::DpadUp);
	//dae::InputManager::GetInstance().AddInputAction(L"MoveRight", dae::ControllerInput::JoyStickLeft);
	////dae::InputManager::GetInstance().AddInputAction(L"MoveRight", dae::ControllerInput::DpadLeft);

	//dae::InputManager::GetInstance().AddInputAction(L"MoveLeft", dae::ControllerInput::DpadLeft);

	m_IsInitialized = true;
}

void TestScene::Update()
{
	if (dae::InputManager::GetInstance().IsPressed(L"MoveUp",0))
	{
		dae::Logger::LogInfo(L"MOVING UP PRESSED");
	}
	if (obj1->GetComponent<dae::ColliderComponent>()->IsCollidingWith(obj2))
	{
		//dae::Logger::LogInfo(L"COLLISION");
	}
	//if (dae::InputManager::GetInstance().IsReleased("MoveUp"))
	//{
	//	dae::Logger::LogInfo("MOVING UP RELEASED");
	//}
	//if (dae::InputManager::GetInstance().IsHolding("MoveUp"))
	//{
	//	dae::Logger::LogInfo("MOVING UP HOLDING");
	//}
	//if (dae::InputManager::GetInstance().GetControllerAxis("MoveRight").x > 0.5f)
	//{
	//	dae::Logger::LogInfo("MOVING Right with more than 0.5f X");
	//}
	//dae::InputManager::GetInstance().GetControllerAxis("MoveLeft");
	//dae::InputManager::GetInstance().IsPressed("MoveRight");

}

void TestScene::Render() const
{

}

void TestScene::OnCollisionStart()
{

}

void TestScene::OnCollisionEnd()
{

}
