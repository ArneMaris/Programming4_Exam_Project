#include "MiniginPCH.h"
#include "TestScene.h"
#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"


TestScene::TestScene(bool autoInit)
	:dae::Scene("TestScene")
{
	if (autoInit)
		Initialize();
}

void TestScene::Initialize()
{
	if (m_IsInitialized)
		return;

	auto obj = new dae::GameObject();
	obj->AddComponent(new dae::SpriteComponent("background.jpg"));
	AddGameObject(obj);

	obj = new dae::GameObject();
	obj->SetPosition(216, 180);
	obj->AddComponent(new dae::SpriteComponent("logo.png"));
	AddGameObject(obj);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	obj = new dae::GameObject();
	obj->SetPosition(80, 20);
	obj->AddComponent(new dae::TextComponent(font, "Programming 4 Assignment"));
	AddGameObject(obj);

	obj = new dae::GameObject();
	obj->AddComponent(new dae::FpsCounterComponent(font));
	AddGameObject(obj);

	obj = new dae::GameObject();
	obj->SetPosition(20, 400);
	obj->AddComponent(new dae::AnimatedSpriteComponent("SpriteTest.png", 4,2));
	obj->GetComponent<dae::AnimatedSpriteComponent>()->SetSecondsPerFrame(0.5f);
	obj->GetComponent<dae::AnimatedSpriteComponent>()->SetScale(4);
	AddGameObject(obj);

	//testing the limits on the sprite to only play the sheet partially
	obj = new dae::GameObject();
	obj->SetPosition(80, 400);
	obj->AddComponent(new dae::AnimatedSpriteComponent("SpriteTest.png", 4, 2));
	obj->GetComponent<dae::AnimatedSpriteComponent>()->SetSecondsPerFrame(0.5f);
	obj->GetComponent<dae::AnimatedSpriteComponent>()->SetScale(4);
	obj->GetComponent<dae::AnimatedSpriteComponent>()->SetRowLimit(1, 1);
	//obj->GetComponent<dae::AnimatedSpriteComponent>()->SetColumnLimit(1, 2);
	obj->GetComponent<dae::AnimatedSpriteComponent>()->SetColumnLimit(3, 4);
	AddGameObject(obj);

	m_IsInitialized = true;
}
void TestScene::Update()
{

}

void TestScene::Render() const
{

}
