#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "Texture2D.h"


dae::TextComponent::TextComponent(const std::string& text, Font* font)
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_pFont(font)
	, m_pTexture(nullptr)
{ 
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
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

void dae::TextComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_pGameObject->GetPosition();
		Renderer::GetInstance().RenderTexture(m_pTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetTextOffset(glm::vec2 newOffset)
{
	m_Offset = newOffset;
}

const glm::vec2& dae::TextComponent::GetTextOffset() const
{
	return m_Offset;
}


