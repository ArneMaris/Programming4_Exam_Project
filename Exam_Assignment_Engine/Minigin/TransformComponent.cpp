#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "PhysicsBodyComponent.h"

dae::TransformComponent::TransformComponent()
	:m_Position{0,0}
	,m_Rotation{0}
	, m_TargetPos{-1,-1}
	, m_TargetSeekSpeed{-1}
	, m_Seeking{false}
{

}

void dae::TransformComponent::SetPosition(const float x, const float y)
{
	SetPosition({ x,y });
}

void dae::TransformComponent::SetRotation(float rotInDegrees)
{
	if (m_pPhysicsBody != nullptr && m_pGameObject->m_Initialized)
	{
		m_pPhysicsBody->SetTransform(m_pPhysicsBody->GetPosition(), DegreesToRad(rotInDegrees));
	}
	else
	{
		m_Rotation = rotInDegrees;
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

bool dae::TransformComponent::MoveToPosition(const b2Vec2 & pos, float speed, bool force)
{
	//if lenght is very short (reached destination)
	if (force || !m_Seeking)
	{
		m_TargetPos = pos;
		m_TargetSeekSpeed = speed;
		m_Seeking = true;
		return true;
	}
	return false;
}

void dae::TransformComponent::Rotate(float rotInDegrees)
{
	if (m_pPhysicsBody != nullptr && m_pGameObject->m_Initialized)
	{
		if (m_pPhysicsBody->GetType() == b2_dynamicBody)
		{
			Logger::GetInstance().LogWarning(L"Rotating a dynamic body (undefined behavior)! use AddTorque on PhysicsBodyComponent instead!");
		}
		m_pPhysicsBody->SetTransform(m_pPhysicsBody->GetPosition(), m_pPhysicsBody->GetAngle() + DegreesToRad(rotInDegrees));
	}
	else
	{
		m_Rotation += rotInDegrees;
	}
	
}

void dae::TransformComponent::Update()
{
	if (m_pPhysicsBody != nullptr)
	{
		m_Position = m_pPhysicsBody->GetPosition();
		m_Rotation = RadToDegrees(m_pPhysicsBody->GetAngle());
	}

	if (!m_Seeking) return;

	float distanceToTarget = float(b2Distance(m_TargetPos, m_Position));
	if (distanceToTarget > m_TargetSeekSpeed * 0.01f)
	{
		b2Vec2 moveDir = (m_TargetPos - m_Position);
		moveDir.Normalize();
		//moveDir.x /= distanceToTarget;
		//moveDir.y /= distanceToTarget;
		moveDir *= m_TargetSeekSpeed * GameInfo::deltaTime;
		Translate(moveDir);
	}
	else
	{
		m_Seeking = false;
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
