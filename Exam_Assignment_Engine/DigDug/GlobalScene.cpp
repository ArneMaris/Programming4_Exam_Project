#include "pch.h"
#include "GlobalScene.h"
#include "Components.h"
#include "MenuAndHud.h"
#include "SceneManager.h"

GlobalScene::GlobalScene()
	:dae::Scene(L"GlobalScene", { 0,0 })
{
	dae::SceneManager::GetInstance().SetGlobalSceneRenderFront(false);
}

void GlobalScene::Initialize()
{
	auto menuAndHud = new dae::GameObject();
	menuAndHud->SetName(L"MenuHud");
	menuAndHud->AddComponent(new dae::ScriptComponent(new MenuAndHud()));
	AddGameObject(menuAndHud);

	auto back = new dae::GameObject();
	back->SetRenderOrder(-1);
	back->AddComponent(new dae::SpriteComponent("Background.png"));
	back->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth / 2), float(dae::GameInfo::windowHeight / 2));
	AddGameObject(back);
}

void GlobalScene::Update()
{

}

void GlobalScene::Render() const
{

}


