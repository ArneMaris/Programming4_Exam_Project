#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent()
	:m_Position{0,0}
	,m_Rotation{0}
{

}

void dae::TransformComponent::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void dae::TransformComponent::SetRotation(float rot)
{
	m_Rotation = rot;
}

void dae::TransformComponent::SetPosition(const b2Vec2 & pos)
{
	m_Position = pos;
}

void dae::TransformComponent::Translate(float x, float y)
{
	m_Position.x += x;
	m_Position.y += y;
}

void dae::TransformComponent::Translate(b2Vec2 & pos)
{
	m_Position.x += pos.x;
	m_Position.y += pos.y;
}

void dae::TransformComponent::Rotate(float angle)
{
	m_Rotation += angle;
}

void dae::TransformComponent::Update()
{

}

void dae::TransformComponent::Initialize()
{
}

void dae::TransformComponent::Render() const
{
}
