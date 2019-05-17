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

	auto backGroundLevel = new dae::GridLevel(L"Level1Back.txt", false);
	backGroundLevel->AddTileConfiguration(0, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/Empty.png"), false));
	backGroundLevel->AddTileConfiguration(1, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/Layer1.png"), false));
	backGroundLevel->AddTileConfiguration(2, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/Layer2.png"), false));
	backGroundLevel->AddTileConfiguration(3, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/Layer3.png"), false));
	backGroundLevel->AddTileConfiguration(4, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/Layer4.png"), false));

	//DIGDUG Spawn
	dae::TileByNrConnections tileNrConSettings;
	dae::TileRotationsByConnections tileRotByConSettings;
	backGroundLevel->AddTileConfiguration(5, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/Layer1.png"), false, new DigDug()));

	auto overlayLevel = new dae::GridLevel(L"Level1Tunnels.txt", true);
	overlayLevel->AddTileConfiguration(0, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/Empty.png"), true));
	overlayLevel->AddTileConfiguration(1, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/Air.png"), false));
	overlayLevel->AddTileConfiguration(2, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/TunnelEnd.png"), true));
	overlayLevel->AddTileConfiguration(3, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/TunnelPassS.png"), true));
	overlayLevel->AddTileConfiguration(4, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/TunnelPassC.png"), true));
	overlayLevel->AddTileConfiguration(5, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/TunnelT.png"), true));
	overlayLevel->AddTileConfiguration(6, dae::TileSettings(dae::ResourceManager::GetInstance().LoadTexture(L"Tiles/TunnelOpen.png"), true));

	AddLevel(backGroundLevel);
	AddLevel(overlayLevel);

	EnablePhysicsDebugDrawing();

	m_IsInitialized = true;
}

void TestScene::Update()
{
	auto obj = GetGameObject(L"DigDug");
	auto lastTile = GetLevels()[1]->GetTileByPos(obj->GetTransform()->GetPosition());
	UNREFERENCED_PARAMETER(lastTile);
}

void TestScene::Render() const
{

}
