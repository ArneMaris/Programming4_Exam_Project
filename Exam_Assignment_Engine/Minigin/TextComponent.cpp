#include "MiniginPCH.h"

#include "TextComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Utility.h"

dae::TextComponent::TextComponent(std::shared_ptr<TTF_Font> font, const std::string& text, const SDL_Color& color)
	: m_NeedsUpdate(true)
	, m_Text(std::move(text))
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
		const auto surf = TTF_RenderText_Blended(m_pFont.get(), reinterpret_cast<const char*>(m_Text.c_str()), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		m_pTexture = nullptr;
		auto texture = SDL_SharedPointer(SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf));
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		m_pTexture = texture;
		if (m_pTexture != nullptr)
			SDL_QueryTexture(m_pTexture.get(), static_cast<Uint32>(SDL_PIXELFORMAT_UNKNOWN), static_cast<int>(SDL_TEXTUREACCESS_STATIC), &m_TextureWidth, &m_TextureHeight);

		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Initialize()
{
}

void dae::TextComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		auto pos = m_pGameObject->GetTransform()->GetPosition();
		pos.x -= m_TextureWidth / 2;
		pos.y += m_TextureHeight / 2;
		Renderer::GetInstance().RenderTexture(m_pTexture, pos.x, pos.y, m_pGameObject->GetTransform()->GetRotationDegrees());
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = std::move(text);
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


