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
	obj->AddComponent(new dae::TextComponent("Programming 4 Assignment", font));
	obj->AddComponent(new dae::FpsCounterComponent(font));
	AddGameObject(obj);
	m_IsInitialized = true;
}
void TestScene::Update()
{

}

void TestScene::Render() const
{

}
