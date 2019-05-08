#include "MiniginPCH.h"
#include "AnimatedSpriteComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"

dae::AnimatedSpriteComponent::AnimatedSpriteComponent(const std::wstring& assetName, int nrCols, int nrRows,
	float scale, float secPerFrame, const b2Vec2& offset, const FlipDirection& flipDir, float angle, const b2Vec2& rotationCenter)
	:SpriteComponent(assetName, scale, offset)
	, m_Cols{ nrCols }
	, m_Rows{ nrRows }
	, m_SecPerFrame{ secPerFrame }
	, m_AccuSec{ 0 }
	, m_CurrRow{ 0 }
	, m_CurrColumn{ 0 }
	, m_FlipDirection {flipDir}
	, m_MinColumn{1}
	, m_MinRow {1}
	, m_MaxColumn{nrCols}
	, m_MaxRow{nrRows}
	, m_Angle{ angle }
	, m_RotationCenter{ int(rotationCenter.x), int(rotationCenter.y) }
{
}

dae::AnimatedSpriteComponent::AnimatedSpriteComponent(const std::wstring & assetName, int nrCols, int nrRows, float secPerFrame)
	:SpriteComponent(assetName, 1, { 0,0 })
	, m_Cols{ nrCols }
	, m_Rows{ nrRows }
	, m_SecPerFrame{ secPerFrame }
	, m_AccuSec{ 0 }
	, m_CurrRow{ 1 }
	, m_CurrColumn{ 1 }
	, m_FlipDirection{ FlipDirection::none }
	, m_MinColumn{ 1 }
	, m_MinRow{ 1 }
	, m_MaxColumn{ nrCols }
	, m_MaxRow{ nrRows }
	, m_Angle{ 0 }
	, m_RotationCenter{ 0,0 }
{
}

void dae::AnimatedSpriteComponent::Update()
{
	m_AccuSec += GameInfo::deltaTime;
	if (m_SecPerFrame < m_AccuSec)
	{
		++m_CurrColumn;
		if (m_CurrColumn > m_MaxColumn)
		{
			m_CurrColumn = m_MinColumn;
			++m_CurrRow;
			if (m_CurrRow > m_MaxRow)
			{
				m_CurrRow = m_MinRow;
			}
		}
		m_AccuSec -= m_SecPerFrame;
	}
}

void dae::AnimatedSpriteComponent::Initialize()
{
}

void dae::AnimatedSpriteComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		auto pos = m_pGameObject->GetTransform()->GetPosition();
		auto rot = m_pGameObject->GetTransform()->GetRotation();
		int frameWidth{ m_TextureWidth / m_Cols };
		int frameHeight{ m_TextureHeight / m_Rows };
		SDL_Rect destRect{ int(pos.x + m_Offset.x), int(pos.y + m_Offset.y), int(frameWidth * m_Scale), int(frameHeight * m_Scale) };
		SDL_Rect srcRect{ frameWidth * (m_CurrColumn-1), frameHeight * (m_CurrRow-1), frameWidth, frameHeight };
		SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
		switch (m_FlipDirection)
		{
		case dae::AnimatedSpriteComponent::vertical:
			flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
			srcRect = { frameWidth * (m_CurrColumn - 1), m_TextureHeight - (frameHeight * (m_CurrRow - 1)), frameWidth, m_TextureHeight - frameHeight };
			break;
		case dae::AnimatedSpriteComponent::horizontal:
			flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
			srcRect = { m_TextureWidth - (frameWidth * (m_CurrColumn - 1)), frameHeight * (m_CurrRow - 1), m_TextureWidth - frameWidth, frameHeight };
			break;
		}

		Renderer::GetInstance().RenderTexture(m_pTexture, destRect, srcRect, rot + m_Angle, { int(pos.x) + m_RotationCenter.x, int(pos.y) + m_RotationCenter.y }, flip);
	}
}


void dae::AnimatedSpriteComponent::SetFlipDirection(const FlipDirection & flipDir)
{
	m_FlipDirection = flipDir;
}

void dae::AnimatedSpriteComponent::SetAngleDegrees(float newAngle)
{
	m_Angle = newAngle;
}

void dae::AnimatedSpriteComponent::SetAngleRadians(float newAngle)
{
	m_Angle = float(newAngle * 180 / M_PI);
}

void dae::AnimatedSpriteComponent::SetRotationCenter(b2Vec2 newCenter)
{
	m_RotationCenter = { int(newCenter.x), int(newCenter.y) };
}

void dae::AnimatedSpriteComponent::SetActiveRow(int newRow, bool reset)
{
	m_CurrRow = newRow;

	if (reset)
		m_AccuSec = 0;
}

void dae::AnimatedSpriteComponent::SetActiveColumn(int newColumn, bool reset)
{
	m_CurrColumn = newColumn;

	if (reset)
		m_AccuSec = 0;
}

void dae::AnimatedSpriteComponent::AddAnimation(const Animation& animation, bool autoPlay)
{
	m_Animations.insert(std::pair<const std::wstring, const Animation>(animation.animationName, animation));

	if (autoPlay)
		PlayAnimation(animation.animationName);
}

void dae::AnimatedSpriteComponent::PlayAnimation(const std::wstring & name)
{
	auto it = m_Animations.find(name);
	if (it != m_Animations.end())
	{
		SetRowLimit(it->second.minRow, it->second.maxRow);
		SetColumnLimit(it->second.minColumn, it->second.maxColumn);
		m_SecPerFrame = it->second.secPerFrame;
	}
}

void dae::AnimatedSpriteComponent::SetRowLimit(int min, int max)
{
	if (min > 0)
		m_MinRow = min;

	if (max <= m_Rows)
		m_MaxRow = max;

	if (m_CurrRow < m_MinRow) m_CurrRow = m_MinRow;
	if (m_CurrRow > m_MaxRow) m_CurrRow = m_MaxRow;
}

void dae::AnimatedSpriteComponent::SetColumnLimit(int min, int max)
{
	if (min > 0)
		m_MinColumn = min;

	if (max <= m_Cols)
		m_MaxColumn = max;

	if (m_CurrColumn < m_MinColumn) m_CurrColumn = m_MinColumn;
	if (m_CurrColumn > m_MaxColumn) m_CurrColumn = m_MaxColumn;
}

void dae::AnimatedSpriteComponent::SetSecondsPerFrame(float newSecPerFrame)
{
	m_SecPerFrame = newSecPerFrame;
	m_AccuSec = 0;
}

int dae::AnimatedSpriteComponent::GetNrFrames() const
{
	return m_Cols * m_Rows;
}
