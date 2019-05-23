#include "pch.h"
#include "DigDugLevel.h"
#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameInfo.h"
#include "Prefabs.h"
#include "GridLevel.h"
#include "MenuAndHud.h"

DigDugLevel::DigDugLevel(const std::string& levelPath)
	:dae::Scene(L"DigDug" + std::wstring(levelPath.begin(), levelPath.end()), { 0,0 })
	, m_LevelPath{std::move(levelPath)}
	//set the sceneName and gravity here
{
}

void DigDugLevel::Initialize()
{
	dae::Logger::GetInstance().EnableInfoLogging();
	auto& resourceManager = dae::ResourceManager::GetInstance();

	auto backGroundLevel = new dae::GridLevel(m_LevelPath + "Back.txt", false, { 0,0 });
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
	
	auto overlayLevel = new dae::GridLevel(m_LevelPath + "Tunnels.txt", true, tileRotByConSettings, tileNrConSettings, { 0,0 });
	overlayLevel->AddTileConfiguration(0, dae::TileSettings(resourceManager.LoadTexture("Tiles/Empty.png"), false, true));
	overlayLevel->AddTileConfiguration(2, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelEnd.png"), true,true));
	overlayLevel->AddTileConfiguration(3, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelPassS.png"), true,true));
	overlayLevel->AddTileConfiguration(4, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelPassC.png"), true,true));
	overlayLevel->AddTileConfiguration(5, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelT.png"), true,true));
	overlayLevel->AddTileConfiguration(6, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelOpen.png"), true,true));

	//Spawns

	if (static_cast<MenuAndHud*>(dae::GetObjByNameGlobalScene(L"MenuHud")->GetComponent<dae::ScriptComponent>()->GetScript())->GetIsTwoPlayers())
	{
		overlayLevel->AddTileConfiguration(10, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelOpen.png"), true, true, new DigDug(false)));
	}
	else
	{
		overlayLevel->AddTileConfiguration(10, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelOpen.png"), true, true));
	}
	overlayLevel->AddTileConfiguration(1, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelOpen.png"), true, true, new DigDug()));
	overlayLevel->AddTileConfiguration(7, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelOpen.png"), true, true, new Pooka()));
	overlayLevel->AddTileConfiguration(8, dae::TileSettings(resourceManager.LoadTexture("Tiles/TunnelOpen.png"), true, true, new Fygar()));
	overlayLevel->AddTileConfiguration(9, dae::TileSettings(resourceManager.LoadTexture("Tiles/Empty.png"), false, true, new Stone()));

	AddLevel(backGroundLevel);
	AddLevel(overlayLevel);

	EnablePhysicsDebugDrawing();
}

void DigDugLevel::RemoveEnemy()
{
	--m_EnemiesLeft;
	if (m_EnemiesLeft == 0)
	{
		//DIGDUG WINS, load next scene
   		dae::SceneManager::GetInstance().SetNextSceneActive();
	}
}

void DigDugLevel::Update()
{
}

void DigDugLevel::Render() const
{

}
