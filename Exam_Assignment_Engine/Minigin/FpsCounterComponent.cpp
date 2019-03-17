#include "MiniginPCH.h"
#include "FpsCounterComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"


dae::FpsCounterComponent::FpsCounterComponent(Font* font, Corner corner)
	:m_pFont{font}
	, m_FpsTimer{0}
	, m_FpsCount{0}
	, m_Corner{corner}
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
		m_FpsTimer -= 1.0f;
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), std::to_string(m_FPS).c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = new Texture2D(texture);
	}
}

void dae::FpsCounterComponent::Render() const
{
	glm::vec2 pos{};
	switch (m_Corner)
	{
	case Corner::leftTop:
		pos.x = 0;
		pos.y = 0;
		break;
	case Corner::rightTop:
		pos.x = float(GameInfo::GetInstance().windowWidth - m_pFont->GetFontSize());
		pos.y = float(GameInfo::GetInstance().windowHeight - m_pFont->GetFontSize());
		break;
	case Corner::leftBot:
		pos.x = float(GameInfo::GetInstance().windowWidth);
		pos.y = float(GameInfo::GetInstance().windowHeight);
		break;
	case Corner::rightBot:
		pos.x = float(GameInfo::GetInstance().windowWidth - m_pFont->GetFontSize());
		pos.y = float(GameInfo::GetInstance().windowHeight);
		break;
	}
	if (m_pTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(m_pTexture, pos.x, pos.y);
	}
}
