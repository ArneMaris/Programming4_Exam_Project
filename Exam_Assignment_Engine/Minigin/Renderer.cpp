#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "imgui_sdl.h"

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	else
	{
		Logger::LogInfo("Renderer initialize succesfull!");
	}
}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance().Render();

	//render ImGui
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	
	SDL_RenderPresent(mRenderer);

}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture, nullptr, &dst);
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture, nullptr, &dst);
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, const SDL_Rect& destRect, const SDL_Rect& srcRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture, &srcRect, &destRect);
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, const SDL_Rect& destRect, const SDL_Rect& srcRect, float angle, const SDL_Point& rotationCenter, const SDL_RendererFlip& flip) const
{
	double dbAngle = static_cast<double>(angle);
	SDL_RenderCopyEx(GetSDLRenderer(), texture, &srcRect, &destRect, dbAngle, &rotationCenter, flip);
}
