#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::GameObject()
	:m_pPhysicsWorldRef{nullptr}
{
	m_pTransform = std::make_shared<TransformComponent>();
}

dae::GameObject::~GameObject()
{
	m_pComponents.clear();
}

void dae::GameObject::Update()
{
	for (std::shared_ptr<BaseComponent> comp : m_pComponents)
	{
		comp->Update();
	}
}


void dae::GameObject::Render() const
{
	for (std::shared_ptr<BaseComponent> comp : m_pComponents)
	{
		comp->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_pTransform->SetPosition(x, y, 0.0f);
}

const b2Vec3 dae::GameObject::GetPosition()
{
	return m_pTransform->GetPosition();
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> pComp)
{
	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = std::shared_ptr<GameObject>(this);
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> pComp)
{
	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);
	m_pComponents.erase(it);
	pComp->m_pGameObject = nullptr;
}

void dae::GameObject::SetPhysicsWorld(b2World * physicsWorld)
{
	m_pPhysicsWorldRef = physicsWorld;
}

b2World *dae::GameObject::GetPhysicsWorld()
{
	return m_pPhysicsWorldRef;
}

