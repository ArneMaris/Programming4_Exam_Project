#include "pch.h"
#include "Game.h"
#include "SceneManager.h"
#include "DigDugLevel.h"
#include "GlobalScene.h"

Game::Game()
{
	dae::GameInfo::windowWidth = 920;
	dae::GameInfo::windowHeight = 920;
}

// MAKE YOUR GAME HERE!
//after this function the engine starts running so you setup everything here!
//Add scenes etc, Scenes get initialized just before engine starts his GameLoop
void Game::SetupGame()
{
	dae::SceneManager& sceneManager = dae::SceneManager::GetInstance();
	sceneManager.AddGlobalScene(new GlobalScene());
	sceneManager.AddScene(new DigDugLevel("Level1"), true);
	sceneManager.AddScene(new DigDugLevel("Level2"), false);
	sceneManager.AddScene(new DigDugLevel("Level3"), false);
	sceneManager.AddScene(new DigDugLevel("Level4"), false);
}
