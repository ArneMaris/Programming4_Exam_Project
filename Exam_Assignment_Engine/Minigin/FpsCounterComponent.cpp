#include "MiniginPCH.h"
#include "FpsCounterComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"


dae::FpsCounterComponent::FpsCounterComponent(Font* font, bool leftTopCorner)
	:m_pFont{font}
	, m_FPS{0}
	, m_FpsCount{0}
	, m_FpsTimer{0}
	, m_LeftTop{ leftTopCorner }
{
}

void dae::FpsCounterComponent::Update()
{
	//FPS LOGIC
	m_FpsTimer += GameInfo::deltaTime;
	++m_FpsCount;
	if (m_FpsTimer >= 1.0f)
	{
		m_FPS = m_FpsCount;
		m_FpsCount = 0;
		m_FpsTimer -= 1;

		SDL_Color color = { 255,0,0 };
		if (m_FPS >= 60)
		{
			color = { 0,255,0 };
		}
		else if (m_FPS >= 30)
		{
			color = { 255,255,0 };
		}
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), (std::to_string(m_FPS)+" FPS").c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		if (m_pTexture != nullptr)
			SDL_DestroyTexture(m_pTexture);
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = texture;
	}
}

void dae::FpsCounterComponent::Render() const
{
	glm::vec2 pos{0,0};
	if (m_pTexture != nullptr)
	{
		if (!m_LeftTop)
		{
			pos.x = float(GameInfo::GetInstance().windowWidth - m_pFont->GetFontSize() * 1.3f);
			pos.y = 0;
		}
		Renderer::GetInstance().RenderTexture(m_pTexture, pos.x, pos.y);
	}
}
