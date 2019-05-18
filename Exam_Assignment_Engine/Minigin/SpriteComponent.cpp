#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::SpriteComponent::SpriteComponent(const std::string& assetPath, float scale, const b2Vec2& offset, float angle, const b2Vec2& rotationCenter, const SDL_RendererFlip& flipDir)
	: m_pTexture{nullptr}
	, m_Offset{ offset }
	, m_TextureWidth{0}
	, m_TextureHeight{0}
	, m_Scale{scale}
	, m_FlipDirection{ flipDir }
	, m_Angle{ angle }
	, m_RotationCenter{ int(rotationCenter.x), int(rotationCenter.y) }
	, m_DoRender{ true }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(assetPath);
	if (m_pTexture != nullptr)
		SDL_QueryTexture(m_pTexture.get(), static_cast<Uint32>(SDL_PIXELFORMAT_UNKNOWN), static_cast<int>(SDL_TEXTUREACCESS_STATIC), &m_TextureWidth, &m_TextureHeight);
}

void dae::SpriteComponent::Update()
{

}

void dae::SpriteComponent::Initialize()
{
}

void dae::SpriteComponent::Render() const
{
	if (m_pTexture != nullptr && m_DoRender)
	{
		auto pos = m_pGameObject->GetTransform()->GetPosition();
		pos.x -= (GetTextureWidth() * m_Scale) / 2;
		pos.y += (GetTextureHeight() * m_Scale) / 2;
		Renderer::GetInstance().RenderTexture(m_pTexture, pos.x + m_Offset.x, pos.y - m_Offset.y, GetTextureWidth() * m_Scale, GetTextureHeight() * m_Scale, m_pGameObject->GetTransform()->GetRotationDegrees());
	}
}

void dae::SpriteComponent::SetSpriteOffset(b2Vec2 newOffset)
{
	m_Offset = newOffset;
}

void dae::SpriteComponent::SetTexture(const std::string& assetPathNewTexture)
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

void dae::SpriteComponent::SetFlipDirection(const SDL_RendererFlip& flipDir)
{
	m_FlipDirection = flipDir;
}

void dae::SpriteComponent::SetAngleDegrees(float newAngle)
{
	m_Angle = newAngle;
}

void dae::SpriteComponent::SetAngleRadians(float newAngle)
{
	m_Angle = RadToDegrees(newAngle);
}

void dae::SpriteComponent::SetRotationCenter(b2Vec2 newCenter)
{
	m_RotationCenter = { int(newCenter.x), int(newCenter.y) };
}