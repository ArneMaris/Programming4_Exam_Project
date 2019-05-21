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
	:dae::Scene(L"TestScene", { 0,0 })
	//set the sceneName and gravity here
{
}

void TestScene::Initialize()
{
	if (m_IsInitialized)
		return;

	dae::Logger::GetInstance().EnableInfoLogging();
	auto& resourceManager = dae::ResourceManager::GetInstance();

	auto backGroundLevel = new dae::GridLevel("Level1Back.txt", false, { 0,0 });
	backGroundLevel->AddTileConfiguration(1, dae::TileSettings(resourceManager.LoadTexture("Tiles/Layer1.png"), false));
	backGroundLevel->AddTileConfiguration(2, dae::TileSettings(resourceManager.LoadTexture("Tiles/Layer2.png"), false));
	backGroundLevel->AddTileConfiguration(3, dae::TileSettings(resourceManager.LoadTexture("Tiles/Layer3.png"), false));
	backGroundLevel->AddTileConfiguration(4, dae::TileSettings(resourceManager.LoadTexture("Tiles/Layer4.png"), false));


	dae::TileByNrConnections tileNrConSettings{ 0,2,3,4,5,6 };
	dae::TileRotationsByConnections tileRotByConSettings{};
	tileRotByConSettings.Down = 180;
	tileRotByConSettings.Left = 270;
	tileRotByConSettings.Right = 90;
	tileRotByConSettings.Up = 0;
	tileRotByConSettings.DownLeft = 180;
	tileRotByConSettings.DownRight = 90;
	tileRotByConSettings.UpLeft = 270;
	tileRotByConSettings.UpRight = 0;
	tileRotByConSettings.LeftRightDown = 90;
	tileRotByConSettings.LeftRightUp = 270;
	tileRotByConSettings.UpDownLeft = 180;
	tileRotByConSettings.UpDownRight = 0;
	tileRotByConSettings.LeftRight = 90;
	tileRotByConSettings.UpDown = 0;
	
	auto overlayLevel = new dae::GridLevel("Level1Tunnels.txt", true, tileRotByConSettings, tileNrConSettings, { 0,0 });
	overlayLevel->AddTileConfiguration(0, dae::TileSettings(resourceManager.LoadTexture("Tiles/Empty.png"), false, true));
	overlayLevel->AddTileConfiguration(2, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelEnd.png"), true,true));
	overlayLevel->AddTileConfiguration(3, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelPassS.png"), true,true));
	overlayLevel->AddTileConfiguration(4, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelPassC.png"), true,true));
	overlayLevel->AddTileConfiguration(5, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelT.png"), true,true));
	overlayLevel->AddTileConfiguration(6, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelOpen.png"), true,true));

	//Spawns
	overlayLevel->AddTileConfiguration(1, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelOpen.png"), true, true, new DigDug()));
	overlayLevel->AddTileConfiguration(7, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelOpen.png"), true, true, new Pooka()));
	overlayLevel->AddTileConfiguration(8, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelOpen.png"), true, true, new Fygar()));

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
