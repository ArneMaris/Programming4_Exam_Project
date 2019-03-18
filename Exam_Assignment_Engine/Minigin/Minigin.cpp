#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Components.h"
#include "vld.h"

//Scene includes
#include "TestScene.h"

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		GameInfo::GetInstance().windowWidth,
		GameInfo::GetInstance().windowHeight,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	SceneManager::GetInstance().AddScene(new TestScene());
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SceneManager::GetInstance().CleanUp();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;

		bool doContinue = true;
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			GameInfo::deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += GameInfo::deltaTime;

			doContinue = input.ProcessInput();

			while (lag >= GameInfo::fixedTime)
			{
				sceneManager.Update();
				lag -= GameInfo::fixedTime;
			}
			renderer.Render();
		}
	}
	Cleanup();
}
