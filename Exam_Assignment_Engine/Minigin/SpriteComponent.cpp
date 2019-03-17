#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::SpriteComponent::SpriteComponent(const std::string assetPath)
	: m_pTexture{nullptr}
	, m_Offset{0,0}
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(assetPath);
}

void dae::SpriteComponent::Update()
{

}

void dae::SpriteComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_pGameObject->GetPosition();
		Renderer::GetInstance().RenderTexture(m_pTexture, pos.x + m_Offset.x, pos.y);
	}
}

void dae::SpriteComponent::SetSpriteOffset(glm::vec2 newOffset)
{
	m_Offset = newOffset;
}

const glm::vec2& dae::SpriteComponent::GetSpriteOffset() const
{
	return m_Offset;
}
