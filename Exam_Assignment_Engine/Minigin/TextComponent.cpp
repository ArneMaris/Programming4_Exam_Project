#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "SDL.h"


dae::TextComponent::TextComponent(Font* font, const std::wstring& text, const SDL_Color& color)
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_pFont(font)
	, m_pTexture(nullptr)
	, m_TextColor{ color }
{ 
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = m_TextColor;
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), reinterpret_cast<const char*>(m_Text.c_str()), color);
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

void dae::TextComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_pGameObject->GetPosition();
		Renderer::GetInstance().RenderTexture(m_pTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::wstring& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetTextColor(const SDL_Color& color)
{
	m_TextColor = color;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetTextOffset(b2Vec2 newOffset)
{
	m_Offset = newOffset;
}

const b2Vec2& dae::TextComponent::GetTextOffset() const
{
	return m_Offset;
}


