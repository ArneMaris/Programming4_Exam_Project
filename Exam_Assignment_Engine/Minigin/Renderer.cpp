#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "imgui_sdl.h"
#include <memory>

void dae::Renderer::Init(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	else
	{
		Logger::LogInfo(L"Renderer initialize succesfull!");
	}
}

void dae::Renderer::Render()
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_Renderer);

}

void dae::Renderer::RenderImGui()
{
	//render ImGui
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());

}

void dae::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();
}

void dae::Renderer::RenderTexture(std::shared_ptr<SDL_Texture> texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.get(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.get(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(std::shared_ptr<SDL_Texture> texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.get(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(std::shared_ptr<SDL_Texture> texture, const SDL_Rect& destRect, const SDL_Rect& srcRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.get(), &srcRect, &destRect);
}

void dae::Renderer::RenderTexture(std::shared_ptr<SDL_Texture> texture, const SDL_Rect& destRect, const SDL_Rect& srcRect, float angle, const SDL_Point& rotationCenter, const SDL_RendererFlip& flip) const
{
	double dbAngle = static_cast<double>(angle);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.get(), &srcRect, &destRect, dbAngle, &rotationCenter, flip);
}
