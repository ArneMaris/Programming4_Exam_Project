#include "MiniginPCH.h"
#include "PhysicsBodyComponent.h"
#include "GameObject.h"
#include "SceneManager.h"

dae::PhysicsBodyComponent::PhysicsBodyComponent(b2BodyType bodyType, bool enableRotation)
	:m_Body{nullptr}
	,m_pPhysicsWorldRef{nullptr}
{
	m_pPhysicsWorldRef = SceneManager::GetInstance().GetPhysicsWorld();
	if (m_pPhysicsWorldRef == nullptr)
	{
		Logger::GetInstance().LogError(L"No physics world to make physicsBodies!");
		return;
	}
	b2BodyDef def{};
	def.type = bodyType;
	m_Body = m_pPhysicsWorldRef->CreateBody(&def);
	m_Body->SetFixedRotation(!enableRotation);
}

dae::PhysicsBodyComponent::PhysicsBodyComponent(b2BodyType bodyType, bool enableRotation, const b2Vec2 & pos, const float rotRadians, float linearDamping, float angularDamping, bool startActive, bool isFastTraveling)
	:m_Body{ nullptr }
	, m_pPhysicsWorldRef{ nullptr }
{
	m_pPhysicsWorldRef = SceneManager::GetInstance().GetPhysicsWorld();
	if (m_pPhysicsWorldRef == nullptr)
	{
		Logger::GetInstance().LogError(L"No physics world to make physicsBodies, component deleted!");
		m_pGameObject->RemoveComponent(this);
		return;
	}
	b2BodyDef def{};
	def.type = bodyType;
	def.position = pos;
	def.angle = rotRadians;
	def.linearDamping = linearDamping;
	def.angularDamping = angularDamping;
	def.active = startActive;
	def.bullet = isFastTraveling;
	m_Body = m_pPhysicsWorldRef->CreateBody(&def);
	m_Body->SetFixedRotation(!enableRotation);
}

b2Body* dae::PhysicsBodyComponent::GetPhysicsBody() const
{
	if (m_Body == nullptr)
	{
		Logger::GetInstance().LogError(L"Trying to get nullptr body!");
		return nullptr;
	}
	return m_Body;
}

void dae::PhysicsBodyComponent::Update()
{

}

void dae::PhysicsBodyComponent::Initialize()
{
	m_Body->SetUserData(GetGameObject());
	m_Body->SetTransform(m_pGameObject->GetTransform()->GetPosition(), m_pGameObject->GetTransform()->GetRotationRadians());
}


 void dae::PhysicsBodyComponent::ApplyForce(const b2Vec2 & force, const b2Vec2 & point)
{
	m_Body->ApplyForce(force, point, true);
}

 void dae::PhysicsBodyComponent::ApplyTorque(float torque)
{
	m_Body->ApplyTorque(torque, true);
}

 void dae::PhysicsBodyComponent::ApplyLinearImpulse(const b2Vec2 & impulse, const b2Vec2 & point)
{
	m_Body->ApplyLinearImpulse(impulse, point, true);
}

 void dae::PhysicsBodyComponent::ApplyAngularImpulse(float impulse)
{
	m_Body->ApplyAngularImpulse(impulse, true);
}

void dae::PhysicsBodyComponent::Render() const
{

}
