#include "MiniginPCH.h"
#include "TransformComponent.h"

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Positions.x = x;
	m_Positions.y = y;
	m_Positions.z = z;
}
