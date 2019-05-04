#pragma once
#include "Singleton.h"
#include "SDL_render.h"

namespace dae
{
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void RenderImGui();
		void Destroy();

		void RenderTexture(std::shared_ptr<SDL_Texture> texture, float x, float y) const;
		void RenderTexture(std::shared_ptr<SDL_Texture> texture, float x, float y, float width, float height) const;
		void RenderTexture(std::shared_ptr<SDL_Texture> texture, const SDL_Rect& destRect, const SDL_Rect& srcRect) const;
		void RenderTexture(std::shared_ptr<SDL_Texture> texture, const SDL_Rect& destRect, const SDL_Rect& srcRect, float angle, const SDL_Point& rotationCenter, const SDL_RendererFlip& flip) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	};
}

