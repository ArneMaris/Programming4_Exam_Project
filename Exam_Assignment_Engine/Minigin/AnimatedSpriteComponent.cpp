#include "MiniginPCH.h"
#include "AnimatedSpriteComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"
#include "AnimationResponse.h"
#include "StateMachineComponent.h"
#include "Observer.h"

dae::AnimatedSpriteComponent::AnimatedSpriteComponent(const std::string& assetName, unsigned int nrCols, unsigned int nrRows,
	const b2Vec2 scale, float secPerFrame, const b2Vec2& offset, const SDL_RendererFlip& flipDir, float angle, const b2Vec2& rotationCenter)
	:SpriteComponent(assetName, scale, offset, angle, rotationCenter, flipDir)
	, m_Cols{ nrCols }
	, m_Rows{ nrRows }
	, m_SecPerFrame{ secPerFrame }
	, m_AccuSec{ 0 }
	, m_CurrRow{ 0 }
	, m_CurrColumn{ 0 }
	, m_MinColumn{1}
	, m_MinRow {1}
	, m_MaxColumn{nrCols}
	, m_MaxRow{nrRows}
	, m_pCurrAnimationResponse{ nullptr }
{
}

dae::AnimatedSpriteComponent::AnimatedSpriteComponent(const std::string & assetName, unsigned int nrCols, unsigned int nrRows, float secPerFrame)
	:SpriteComponent(assetName, { 1,1 }, { 0,0 })
	, m_Cols{ nrCols }
	, m_Rows{ nrRows }
	, m_SecPerFrame{ secPerFrame }
	, m_AccuSec{ 0 }
	, m_CurrRow{ 1 }
	, m_CurrColumn{ 1 }
	, m_MinColumn{ 1 }
	, m_MinRow{ 1 }
	, m_MaxColumn{ nrCols }
	, m_MaxRow{ nrRows }
	, m_pCurrAnimationResponse{ nullptr }
{
}

dae::AnimatedSpriteComponent::~AnimatedSpriteComponent()
{
	for (auto& anim : m_Animations)
	{
		if (anim.second.animResponse != nullptr)
			delete anim.second.animResponse;
	}
	m_pCurrAnimationResponse = nullptr;
}

void dae::AnimatedSpriteComponent::Update()
{

	if (!m_Paused)
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
		if (m_pCurrAnimationResponse != nullptr)
			m_pCurrAnimationResponse->Update(m_CurrRow, m_CurrColumn);
	}
}

void dae::AnimatedSpriteComponent::Initialize()
{
	if (m_pGameObject->GetComponent<StateMachineComponent>() != nullptr)
	{
		for (auto anim : m_Animations)
		{
			if (anim.second.animResponse != nullptr)
			{
				for (auto& trans : m_pGameObject->GetComponent<StateMachineComponent>()->GetStateTransitions())
				{
					anim.second.animResponse->AddObserver(std::reinterpret_pointer_cast<Observer>(trans));
				}
			}
		}
	}
}

void dae::AnimatedSpriteComponent::Render() const
{
	if (m_pTexture != nullptr && m_DoRender)
	{
		auto pos = m_pGameObject->GetTransform()->GetPosition();
		auto rot = m_pGameObject->GetTransform()->GetRotationDegrees();
		unsigned int frameWidth{ m_TextureWidth / m_Cols };
		unsigned int frameHeight{ m_TextureHeight / m_Rows };
		pos.x -= (frameWidth * m_Scale.x) / 2;
		pos.y += (frameHeight * m_Scale.y) / 2;
		SDL_Rect destRect{ int(pos.x + m_Offset.x), int(pos.y + m_Offset.y), int(frameWidth * m_Scale.x), int(frameHeight * m_Scale.y) };
		SDL_Rect srcRect{ int(frameWidth * (m_CurrColumn-1)), int(frameHeight * (m_CurrRow-1)), int(frameWidth), int(frameHeight) };

		Renderer::GetInstance().RenderTexture(m_pTexture, destRect, srcRect, rot + m_Angle, { m_RotationCenter.x, m_RotationCenter.y }, m_FlipDirection);
	}
}




void dae::AnimatedSpriteComponent::SetActiveRow(unsigned int newRow, bool reset)
{
	m_CurrRow = newRow;

	if (reset)
		m_AccuSec = 0;
}

void dae::AnimatedSpriteComponent::SetActiveColumn(unsigned int newColumn, bool reset)
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
		m_pCurrAnimationResponse = it->second.animResponse;
	}
}

void dae::AnimatedSpriteComponent::ResetAnimationEventTriggers()
{
	for (auto anim : m_Animations)
	{
		if (anim.second.animResponse != nullptr)
		{
			anim.second.animResponse->ResetTrigger();
		}
	}
}

void dae::AnimatedSpriteComponent::SetRowLimit(unsigned int min, unsigned int max)
{
	if (min > 0)
		m_MinRow = min;

	if (max <= m_Rows)
		m_MaxRow = max;

	if (m_CurrRow < m_MinRow) m_CurrRow = m_MinRow;
	if (m_CurrRow > m_MaxRow) m_CurrRow = m_MaxRow;
}

void dae::AnimatedSpriteComponent::SetColumnLimit(unsigned int min, unsigned int max)
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

unsigned int dae::AnimatedSpriteComponent::GetNrFrames() const
{
	return m_Cols * m_Rows;
}
