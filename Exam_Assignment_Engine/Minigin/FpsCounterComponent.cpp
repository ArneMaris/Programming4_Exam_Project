#include "MiniginPCH.h"
#include "FpsCounterComponent.h"
#include <SDL.h>
#include "GameObject.h"
#include "Renderer.h"


dae::FpsCounterComponent::FpsCounterComponent(std::shared_ptr<TTF_Font> font, bool leftTopCorner)
	: m_FPS{0}
	, m_FpsCount{0}
	, m_FpsTimer{0}
	, m_LeftTop{ leftTopCorner }
{
	m_pGameObject->AddComponent(new TextComponent(font, "0"));
	m_pTextComp = m_pGameObject->GetComponent<TextComponent>();
}

void dae::FpsCounterComponent::Update()
{
	if (m_pTextComp->m_pGameObject == nullptr)
		m_pTextComp->m_pGameObject = GetGameObject();
	//FPS LOGIC
	m_FpsTimer += GameInfo::deltaTime;
	++m_FpsCount;
	if (m_FpsTimer >= 1.0f)
	{
		m_FPS = m_FpsCount;
		m_FpsCount = 0;
		m_FpsTimer -= 1;
		m_pTextComp->m_Text = std::to_string(m_FPS);
		SDL_Color color = { 255,0,0 };
		if (m_FPS >= 60)
		{
			color = { 0,255,0 };
		}
		else if (m_FPS >= 30)
		{
			color = { 255,255,0 };
		}
		m_pTextComp->m_TextColor = color;
	}
	m_pTextComp->Update();
}

void dae::FpsCounterComponent::Initialize()
{
}

void dae::FpsCounterComponent::Render() const
{
	m_pTextComp->Render();
}
