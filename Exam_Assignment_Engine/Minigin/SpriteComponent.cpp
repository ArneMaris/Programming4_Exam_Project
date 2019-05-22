#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::SpriteComponent::SpriteComponent(const std::string& assetPath, const b2Vec2& scale, const b2Vec2& offset, float angle, const b2Vec2& rotationCenter, const SDL_RendererFlip& flipDir)
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
		float rot = m_pGameObject->GetTransform()->GetRotationDegrees() + m_Angle;
		pos.x -= (GetTextureWidth() * m_Scale.x) / 2;
		pos.y += (GetTextureHeight() * m_Scale.y) / 2;

		auto offset = m_Offset;
		float angle = DegreesToRad(m_Angle);
		float cs = cos(angle);
		float sn = sin(angle);
		offset.x = m_Offset.x * cs - m_Offset.y * sn;
		offset.y = m_Offset.x * sn + m_Offset.y * cs;
		if (m_FlipDirection == SDL_FLIP_HORIZONTAL)
			offset.x *= -1;
		else if (m_FlipDirection == SDL_FLIP_VERTICAL)
			offset.y *= -1;

		Renderer::GetInstance().RenderTexture(m_pTexture, pos.x + offset.x, pos.y - offset.y, GetTextureWidth() * m_Scale.x, GetTextureHeight() * m_Scale.y, rot, m_RotationCenter, m_FlipDirection);
	}
}

void dae::SpriteComponent::SetSpriteOffset(const b2Vec2&  newOffset)
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

void dae::SpriteComponent::SetScale(const b2Vec2& newScale)
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