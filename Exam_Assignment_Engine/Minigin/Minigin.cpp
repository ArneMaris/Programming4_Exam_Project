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

//Scene includes
#include "TestScene.h"

void dae::Minigin::Initialize()
{
	// Create ImGui AS ABSOLUTE FIRST (logger works with imGui and initialization message may get printed there
	ImGui::CreateContext();


	GameInfo::GetInstance();
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

void dae::Minigin::LoadGame() const
{
	SceneManager::GetInstance().AddScene(new TestScene());

	SceneManager::GetInstance().Initialize();

	SceneManager::GetInstance().SetActiveScene(L"TestScene");
}

void dae::Minigin::Cleanup()
{
	Logger::GetInstance().LogInfo(L"Cleaning up!");
	Renderer::GetInstance().Destroy(); // also destroys ImGuiSDL renderer
	SceneManager::GetInstance().CleanUp();
	InputManager::GetInstance().CleanUp();
	ResourceManager::GetInstance().CleanUp();

	ImGui_ImplSDL2_Shutdown();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init(L"../Resources/");
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0;

	LoadGame();


	bool doContinue = true;
	while (doContinue)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		GameInfo::deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += GameInfo::deltaTime;
		doContinue = input.ProcessInput(); //process the input for this frame and set the Current Event State to later check for input

		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		sceneManager.Update();
		while (lag >= GameInfo::fixedTime)
		{
			sceneManager.FixedUpdate();
			lag -= GameInfo::fixedTime;
		}

		Logger::GetInstance().Draw();
		
		ImGui::EndFrame();

		renderer.Render(); //also ImGui

		input.SwapInputBuffer(); //swap input buffers after everything is updated;
	}

	Cleanup();
}