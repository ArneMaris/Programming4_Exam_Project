#include "MiniginPCH.h"
#include "FpsCounterComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"


dae::FpsCounterComponent::FpsCounterComponent(Font* font, bool leftTopCorner)
	:m_TextComp{nullptr}
	, m_FPS{0}
	, m_FpsCount{0}
	, m_FpsTimer{0}
	, m_LeftTop{ leftTopCorner }
{;
	m_TextComp = new TextComponent(font, L"0");
}

void dae::FpsCounterComponent::Update()
{
	if (m_TextComp->m_pGameObject == nullptr)
		m_TextComp->m_pGameObject = GetGameObject();
	//FPS LOGIC
	m_FpsTimer += GameInfo::deltaTime;
	++m_FpsCount;
	if (m_FpsTimer >= 1.0f)
	{
		m_FPS = m_FpsCount;
		m_FpsCount = 0;
		m_FpsTimer -= 1;
		m_TextComp->m_Text = std::to_wstring(m_FPS);
		SDL_Color color = { 255,0,0 };
		if (m_FPS >= 60)
		{
			color = { 0,255,0 };
		}
		else if (m_FPS >= 30)
		{
			color = { 255,255,0 };
		}
		m_TextComp->m_TextColor = color;
	}
	m_TextComp->Update();
}

void dae::FpsCounterComponent::Render() const
{
	m_TextComp->Render();
}
