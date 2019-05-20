#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Components.h"
#include "imgui_sdl.h"
#include "SDL_keyboard.h"


void dae::Minigin::Initialize()
{
	// Create ImGui AS ABSOLUTE FIRST (logger works with imGui and initialization message may get printed there
	ImGui::CreateContext();
	Logger::GetInstance();
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	window = SDL_CreateWindow("Programming 4 assignment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GameInfo::windowWidth, GameInfo::windowHeight, window_flags);

	if (window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
	ImGuiSDL::Initialize(Renderer::GetInstance().GetSDLRenderer(), GameInfo::windowWidth, GameInfo::windowHeight);
	ImGui_ImplSDL2_InitForVulkan(window);
}


void dae::Minigin::Run()
{
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Resources/");
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	//initializes all scenes!
	sceneManager.Initialize();

	//start the gameEngine from here!
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0;


	bool doContinue = true;
	while (doContinue)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		GameInfo::deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += GameInfo::deltaTime;

		//process the input for this frame
		doContinue = input.ProcessInput(); 

		//new ImGui frame
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		sceneManager.Update();
		while (lag >= GameInfo::fixedTime)
		{
			sceneManager.FixedUpdate();
			lag -= GameInfo::fixedTime;
		}

		//draw Logger (imGui) information
		Logger::GetInstance().Draw();

		//end ImGui
		ImGui::EndFrame();

		//swap input buffers after everything is updated;
		input.SwapInputBuffer(); 

		//render everything
		renderer.Render(); //also ImGui

	}

	GameInfo::gameEnded = true;
	Cleanup();
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy(); // also destroys ImGuiSDL renderer
	InputManager::GetInstance().CleanUp();
	ResourceManager::GetInstance().CleanUp();
	SceneManager::GetInstance().CleanUp();

	ImGui_ImplSDL2_Shutdown();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}