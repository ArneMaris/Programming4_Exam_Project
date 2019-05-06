#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::GameObject()
	:m_pPhysicsWorldRef{ nullptr }
	, m_Initialized{ false }
{
	AddComponent(new TransformComponent());
}

dae::GameObject::~GameObject()
{
	for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
	{
		delete (*it);
	}
	m_pComponents.clear();
}

void dae::GameObject::Update()
{
	for (BaseComponent* comp : m_pComponents)
	{
		comp->Update();
	}
}


void dae::GameObject::Render() const
{
	for (BaseComponent* comp : m_pComponents)
	{
		comp->Render();
	}
}

void dae::GameObject::Initialize()
{
	if (!m_Initialized)
	{
		for (BaseComponent* comp : m_pComponents)
		{
			comp->Initialize();
		}
		m_Initialized = true;
	}
}

dae::TransformComponent* dae::GameObject::GetTransform() const
{
	return static_cast<TransformComponent*>(m_pComponents.front()); //return first component (always transform cause got added in constructor of gameobject
}

dae::BaseComponent* dae::GameObject::AddComponent(BaseComponent* pComp)
{
	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = this;
	return pComp;
}

void dae::GameObject::RemoveComponent(BaseComponent* pComp)
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
	if (m_pPhysicsWorldRef != nullptr)
		return m_pPhysicsWorldRef;
	else
		return nullptr;
}

