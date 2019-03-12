#pragma once

struct SDL_Window;

namespace dae
{
	class Minigin
	{
		SDL_Window* window{};
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	};
}