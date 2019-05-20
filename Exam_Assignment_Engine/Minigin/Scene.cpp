#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "CollisionCallbacks.h"
#include "Prefab.h"
#include "GridLevel.h"

dae::Scene::Scene(const std::wstring& name, const b2Vec2& gravity) 
	:m_SceneName(name)
	, m_IsInitialized{false}
	, m_IsActive { true }
{ 
	m_pPhysicsWorld = new b2World(gravity);
	m_CollCallbacks = new CollisionCallbacks();
	m_pPhysicsWorld->SetContactListener(m_CollCallbacks);
	if (m_pPhysicsWorld != nullptr)
	{
		Logger::GetInstance().LogInfo(L"PhysicsWorld created succesfully in scene: " + m_SceneName);
	}
}

dae::Scene::~Scene()
{
	for (auto it = m_pObjects.begin(); it != m_pObjects.end(); ++it)
	{
		delete (*it);
		*it = nullptr;
	}
	m_pObjects.clear();

	for (auto it = m_pLevels.begin(); it != m_pLevels.end(); ++it)
	{
		delete (*it);
	}
	m_pLevels.clear();
	
	delete m_CollCallbacks;
	delete m_pPhysicsWorld;
}

void dae::Scene::AddGameObject(GameObject* object)
{
	object->SetPhysicsWorld(m_pPhysicsWorld);
	m_pObjects.push_back(object);
}

void dae::Scene::AddGameObject(Prefab* object)
{
	GameObject* obj = object->Setup();
	delete object; //delete prefab after
	obj->SetPhysicsWorld(m_pPhysicsWorld);
	m_pObjects.push_back(obj);
}

void dae::Scene::AddLevel(GridLevel* level)
{
	if (std::find(m_pLevels.begin(), m_pLevels.end(), level) == m_pLevels.end())
		m_pLevels.push_back(level);
}

const std::wstring & dae::Scene::GetSceneName() const
{
	return m_SceneName;
}

void dae::Scene::BaseUpdate()
{
	Update();
	for(auto& gameObject : m_pObjects)
	{
		gameObject->Update();
	}
}

void dae::Scene::BaseRender() const
{
	Render();

	for (auto& lvl : m_pLevels)
	{
		lvl->Render();
	}

	for (const auto& gameObject : m_pObjects)
	{
		gameObject->Render();
	}
}

void dae::Scene::FixedUpdate()
{
	if (m_pPhysicsWorld != nullptr)
	{
		m_pPhysicsWorld->Step(GameInfo::fixedTime, GameInfo::physicsVelocityIterations, GameInfo::physicsPositionIterations);
	}
}

bool dae::Scene::GetIsActive() const
{
	return m_IsActive;
}

void dae::Scene::SetIsActive(bool value)
{
	m_IsActive = value;
}

b2World* dae::Scene::GetPhysicsWorld() const
{
	return m_pPhysicsWorld;
}

void dae::Scene::ActivateGameObjects()
{
	for (auto& lvl : m_pLevels)
	{
		lvl->Initialize();
	}
	for (auto& gameObject : m_pObjects)
	{
		gameObject->Initialize();
	}
	SortRenderingOrder();
}

void dae::Scene::SortRenderingOrder()
{
	std::sort(m_pObjects.begin(), m_pObjects.end(), [](GameObject* obj1, GameObject* obj2) { return obj1->GetRenderOrder() > obj2->GetRenderOrder(); });
}

dae::GameObject* dae::Scene::GetGameObject(const std::wstring& name)
{
	auto it = std::find_if(m_pObjects.begin(), m_pObjects.end(), [name](GameObject* obj) {return obj->GetName() == name; });
	if (it == m_pObjects.end())
	{
		Logger::GetInstance().LogWarning(L"GameObject with name: " + name + L" not found! Returned nullptr!");
		return nullptr;
	}
	else return *(it);
}
