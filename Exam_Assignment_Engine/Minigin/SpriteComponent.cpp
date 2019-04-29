#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::SpriteComponent::SpriteComponent(const std::wstring& assetPath, float scale, b2Vec2 offset)
	: m_pTexture{nullptr}
	, m_Offset{ offset }
	, m_TextureWidth{0}
	, m_TextureHeight{0}
	, m_Scale{scale}
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(assetPath);
	if (m_pTexture != nullptr)
		SDL_QueryTexture(m_pTexture, static_cast<Uint32>(SDL_PIXELFORMAT_UNKNOWN), static_cast<int>(SDL_TEXTUREACCESS_STATIC), &m_TextureWidth, &m_TextureHeight);
}

void dae::SpriteComponent::Update()
{

}

void dae::SpriteComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_pGameObject->GetPosition();
		Renderer::GetInstance().RenderTexture(m_pTexture, pos.x + m_Offset.x, pos.y + m_Offset.y);
	}
}

void dae::SpriteComponent::SetSpriteOffset(b2Vec2 newOffset)
{
	m_Offset = newOffset;
}

void dae::SpriteComponent::SetTexture(const std::wstring& assetPathNewTexture)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(assetPathNewTexture);
}

const b2Vec2& dae::SpriteComponent::GetSpriteOffset() const
{
	return m_Offset;
}

void dae::SpriteComponent::SetScale(float newScale)
{
	m_Scale = newScale;
}

int dae::SpriteComponent::GetTextureWidth() const
{
	return m_TextureWidth;
}

int dae::SpriteComponent::GetTextureHeight() const
{
	return m_TextureHeight;
}
