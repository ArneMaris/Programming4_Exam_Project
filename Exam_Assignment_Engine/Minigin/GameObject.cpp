#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Components.h"

dae::GameObject::GameObject()
	:m_pPhysicsWorldRef{ nullptr }
	, m_Initialized{ false }
	, m_Name{L"GameObject" + std::to_wstring(GameInfo::amountOfGameObjects+1) }
	, m_RenderOrder{0}
{
	AddComponent(new TransformComponent());
	GameInfo::amountOfGameObjects++;
}

dae::GameObject::GameObject(const std::wstring & name)
	:m_pPhysicsWorldRef{ nullptr }
	, m_Initialized{ false }
	, m_Name{std::move(name)}
{
	AddComponent(new TransformComponent());
	GameInfo::amountOfGameObjects++;
}

dae::GameObject::~GameObject()
{
	for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
	{
		delete (*it);
	}
	m_pComponents.clear();
	GameInfo::amountOfGameObjects--;
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
	for (BaseComponent* comp : m_pComponents)
	{
		comp->PostRender();
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

void dae::GameObject::AddComponent(BaseComponent* pComp)
{
	if (!CheckIfAlreadyHasComponent(pComp))
	{
		m_pComponents.push_back(pComp);
		pComp->m_pGameObject = this;
	}
	else
	{
		Logger::GetInstance().LogError(L"Cant add a second component of this Type!\n (PhysicsBody, Collider or Input");
	}
}

bool dae::GameObject::CheckIfAlreadyHasComponent(BaseComponent * compToAdd)
{
	if (dynamic_cast<PhysicsBodyComponent*>(compToAdd) && GetComponent<PhysicsBodyComponent>() != nullptr)
		return true;
	else if (dynamic_cast<ColliderComponent*>(compToAdd) && GetComponent<ColliderComponent>() != nullptr)
		return true;
	else if (dynamic_cast<ColliderComponent*>(compToAdd) && GetComponent<InputComponent>() != nullptr)
		return true;

	return false;
}

void dae::GameObject::RemoveComponent(BaseComponent* pComp)
{
	pComp->m_pGameObject = nullptr;
	for (auto& pointer : m_pComponents)
	{
		if (pointer == pComp)
		{
			delete pointer;
			pointer = nullptr;
			break;
		}
	}
	m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), nullptr), m_pComponents.end());
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

