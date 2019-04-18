#include "MiniginPCH.h"
#include "PhysicsBodyComponent.h"
#include "GameObject.h"

dae::PhysicsBodyComponent::PhysicsBodyComponent(b2BodyType bodyType)
	:m_Body{nullptr}
	,m_pPhysicsWorldRef{nullptr}
	,m_Fixture{nullptr}
{
	m_pPhysicsWorldRef = GetGameObject()->GetPhysicsWorld();
	b2BodyDef def{};
	def.type = bodyType;
	m_Body = m_pPhysicsWorldRef->CreateBody(&def);
}

dae::PhysicsBodyComponent::PhysicsBodyComponent(b2BodyType bodyType, const b2Vec2 & pos, const float rotRad, float linearDamping, float angularDamping, bool startActive, bool isFastTraveling)
	:m_Body{ nullptr }
	, m_pPhysicsWorldRef{ nullptr }
{
	b2BodyDef def{};
	def.type = bodyType;
	def.position = pos;
	def.angle = rotRad;
	def.linearDamping = linearDamping;
	def.angularDamping = angularDamping;
	def.active = startActive;
	def.bullet = isFastTraveling;
	m_Body = m_pPhysicsWorldRef->CreateBody(&def);
}


void dae::PhysicsBodyComponent::AddCollisionShape(b2Shape * shape)
{
	AddCollisionShape(shape, false, 0.9f, 0.1f, 0.0f);
}

void dae::PhysicsBodyComponent::AddCollisionShape(b2Shape * shape, bool isSensor)
{
	AddCollisionShape(shape, isSensor, 0.9f, 0.1f, 0.0f);
}

void dae::PhysicsBodyComponent::AddCollisionShape(b2Shape* shape, bool isSensor, float density, float friction, float restitution)
{
	if (shape == nullptr)
	{
		Logger::LogWarning("Trying to add an invalid shape to a PhysicsBody!");
		return;
	}
	else if (m_Body == nullptr)
	{
		Logger::LogWarning("Trying to add a shape to an invalid PhysicsBody!");
		return;
	}
	else if (m_Fixture != nullptr)
	{
		Logger::LogInfo("Body already has a fixture, but adding another!");
	}

	b2FixtureDef fixDef{};
	fixDef.shape = shape;
	fixDef.density = density;
	fixDef.friction = friction;
	fixDef.restitution = restitution;
	fixDef.isSensor = isSensor;
	m_Fixture = m_Body->CreateFixture(&fixDef);
}

b2Body * dae::PhysicsBodyComponent::GetPhysicsBody() const
{
	if (m_Body == nullptr)
	{
		Logger::LogError("Trying to get nullptr body!");
	}
	return m_Body;
}

b2Fixture* dae::PhysicsBodyComponent::GetFixture() const
{
	if (m_Fixture == nullptr)
	{
		Logger::LogError("Trying to get nullptr fixture!");
	}
	return m_Fixture;
}

