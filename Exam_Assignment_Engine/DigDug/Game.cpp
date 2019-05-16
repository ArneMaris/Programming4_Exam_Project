#include "pch.h"
#include "Game.h"
#include "SceneManager.h"
#include "TestScene.h"

// MAKE YOUR GAME HERE!
//after this function the engine starts running so you setup everything here!
//Add scenes etc, Scenes get initialized just before engine starts his GameLoop
void Game::SetupGame()
{
	dae::SceneManager& sceneManager = dae::SceneManager::GetInstance();
	sceneManager.AddScene(new TestScene(), true);



}
