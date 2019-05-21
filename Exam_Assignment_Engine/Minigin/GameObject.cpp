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
	, m_Layer{0}
{
	m_TransformComp = new TransformComponent();
	AddComponent(m_TransformComp);
	GameInfo::amountOfGameObjects++;
}

dae::GameObject::GameObject(const std::wstring & name)
	:m_pPhysicsWorldRef{ nullptr }
	, m_Initialized{ false }
	, m_Name{std::move(name)}
{
	m_TransformComp = new TransformComponent();
	AddComponent(m_TransformComp);
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

dae::Script * dae::GameObject::GetScript() const
{
	auto comp = this->GetComponent<dae::ScriptComponent>();
	if (comp != nullptr)
	{
		return comp->GetScript();
	}
	else
	{
		Logger::GetInstance().LogError(L"Trying to get a non existing Script from scriptComponent!");
		return nullptr;
	}
}

void dae::GameObject::Update()
{
	for (auto& comp : m_pComponents)
	{
		comp->Update();
	}
}


void dae::GameObject::Render() const
{
	for (auto& comp : m_pComponents)
	{
		comp->Render();
	}
	for (auto& comp : m_pComponents)
	{
		comp->PostRender();
	}
}

void dae::GameObject::Initialize()
{
	if (!m_Initialized)
	{
		std::vector<BaseComponent*> scriptComps;
		scriptComps.reserve(3);
		for (auto& comp : m_pComponents)
		{
			if (dynamic_cast<ScriptComponent*>(comp))
			{
				scriptComps.push_back(comp);
				m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), comp), m_pComponents.end());
				continue;
			}
			comp->Initialize();
		}
		//makes sure scripts go last (you might wanne set variables in script initialize method from other components, this ensures you dont get nullptr exceptions if you do that
		for (auto& scriptCmp : scriptComps)
		{
			scriptCmp->Initialize();
			//puts the scriptComponents in the back (last updated and rendered to make sure you have all updated components in script
			m_pComponents.push_back(scriptCmp);
		}
		m_Initialized = true;
	}
}

dae::TransformComponent* dae::GameObject::GetTransform() const
{
	return m_TransformComp;
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
		Logger::GetInstance().LogError(L"Cant add a second component of this Type!\n (PhysicsBody, Collider or Input, transform)");
	}
}

bool dae::GameObject::CheckIfAlreadyHasComponent(BaseComponent * compToAdd)
{
	if (dynamic_cast<TransformComponent*>(compToAdd) && GetComponent<TransformComponent>() != nullptr)
		return true;
	else if (dynamic_cast<PhysicsBodyComponent*>(compToAdd) && GetComponent<PhysicsBodyComponent>() != nullptr)
		return true;
	else if (dynamic_cast<ColliderComponent*>(compToAdd) && GetComponent<ColliderComponent>() != nullptr)
		return true;
	else if (dynamic_cast<InputComponent*>(compToAdd) && GetComponent<InputComponent>() != nullptr)
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

