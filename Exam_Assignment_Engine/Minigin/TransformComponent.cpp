#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent()
	:m_Positions{0,0,0}
{
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Positions.x = x;
	m_Positions.y = y;
	m_Positions.z = z;
}

void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::Render() const
{
}
