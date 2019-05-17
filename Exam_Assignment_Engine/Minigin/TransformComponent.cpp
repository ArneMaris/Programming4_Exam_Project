#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "PhysicsBodyComponent.h"

dae::TransformComponent::TransformComponent()
	:m_Position{0,0}
	,m_Rotation{0}
{

}

void dae::TransformComponent::SetPosition(const float x, const float y)
{
	SetPosition({ x,y });
}

void dae::TransformComponent::SetRotation(float rotInRadians)
{
	if (m_pPhysicsBody != nullptr && m_pGameObject->m_Initialized)
	{
		m_pPhysicsBody->SetTransform(m_pPhysicsBody->GetPosition(), rotInRadians);
	}
	else
	{
		m_Rotation = rotInRadians;
	}
}

void dae::TransformComponent::SetPosition(const b2Vec2 & pos)
{
	if (m_pPhysicsBody != nullptr && m_pGameObject->m_Initialized)
	{
		m_pPhysicsBody->SetTransform(pos, m_pPhysicsBody->GetAngle());
	}
	else
	{
		m_Position = pos;
	}
}

void dae::TransformComponent::Translate(float x, float y)
{
	Translate({ x,y });
}

void dae::TransformComponent::Translate(const b2Vec2& pos)
{
	if (m_pPhysicsBody != nullptr && m_pGameObject->m_Initialized)
	{
		if (m_pPhysicsBody->GetType() == b2_dynamicBody)
		{
			Logger::GetInstance().LogWarning(L"Translating a dynamic body (this will teleport it = NO COLLISIONS)! use Addforce on PhysicsBodyComponent instead!");
		}
		m_pPhysicsBody->SetTransform(m_pPhysicsBody->GetPosition() + pos, m_pPhysicsBody->GetAngle());
	}
	else
	{
		m_Position += pos;
	}
}

void dae::TransformComponent::Rotate(float angleInRadians)
{
	if (m_pPhysicsBody != nullptr && m_pGameObject->m_Initialized)
	{
		if (m_pPhysicsBody->GetType() == b2_dynamicBody)
		{
			Logger::GetInstance().LogWarning(L"Rotating a dynamic body (undefined behavior)! use AddTorque on PhysicsBodyComponent instead!");
		}
		m_pPhysicsBody->SetTransform(m_pPhysicsBody->GetPosition(), m_pPhysicsBody->GetAngle() + angleInRadians);
	}
	else
	{
		m_Rotation += angleInRadians;
	}
	
}

void dae::TransformComponent::Update()
{
	if (m_pPhysicsBody != nullptr)
	{
		m_Position = m_pPhysicsBody->GetPosition();
		m_Rotation = m_pPhysicsBody->GetAngle();
	}
}

void dae::TransformComponent::Initialize()
{
	if (m_pGameObject->GetComponent<PhysicsBodyComponent>() != nullptr)
		m_pPhysicsBody = m_pGameObject->GetComponent<PhysicsBodyComponent>()->GetPhysicsBody();
}

void dae::TransformComponent::Render() const
{
}
