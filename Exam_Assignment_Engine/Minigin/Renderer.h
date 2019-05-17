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
		void Destroy();

		void RenderTexture(std::shared_ptr<SDL_Texture> texture, float x, float y) const;
		void RenderTexture(std::shared_ptr<SDL_Texture> texture, float x, float y, float width, float height) const;
		void RenderTexture(std::shared_ptr<SDL_Texture> texture, const float x, const float y, float angle, const SDL_Point& rotationCenter = { NULL,NULL }) const;
		void RenderTexture(std::shared_ptr<SDL_Texture> texture, const float x, const float y, const float w, const float h, float angle, const SDL_Point& rotationCenter = { NULL,NULL }) const;
		void RenderTexture(std::shared_ptr<SDL_Texture> texture, const SDL_Rect& destRect, const SDL_Rect& srcRect) const;
		void RenderTexture(std::shared_ptr<SDL_Texture> texture, const SDL_Rect& destRect, const SDL_Rect& srcRect, float angle, const SDL_Point& rotationCenter = { NULL,NULL }, const SDL_RendererFlip& flip = SDL_RendererFlip::SDL_FLIP_NONE) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	};
}

