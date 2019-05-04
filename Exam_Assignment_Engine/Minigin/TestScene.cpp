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


	auto obj = new dae::GameObject();
	obj->AddComponent(new dae::SpriteComponent(L"background.jpg"));
	obj->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_kinematicBody));
	obj->AddComponent(new dae::ColliderComponent(obj->GetComponent<dae::PhysicsBodyComponent>()));
	AddGameObject(obj);

	obj = new dae::GameObject();
	obj->SetPosition(216, 180);
	obj->AddComponent(new dae::SpriteComponent(L"logo.png"));
	AddGameObject(obj);

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
