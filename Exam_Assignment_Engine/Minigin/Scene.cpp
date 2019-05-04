#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::s_idCounter = 0;

dae::Scene::Scene(const std::wstring& name, const b2Vec2& gravity) 
	:m_SceneName(name)
	, m_IsInitialized{false}
	, m_IsActive { true }
{ 
	m_pPhysicsWorld = new b2World(gravity);
	if (m_pPhysicsWorld != nullptr)
	{
		Logger::LogInfo(L"PhysicsWorld created succesfully in scene: " + m_SceneName);
	}
}

dae::Scene::~Scene()
{
	for (auto it = m_pObjects.begin(); it != m_pObjects.end(); ++it)
	{
		delete (*it);
	}
	m_pObjects.clear();
	
	delete m_pPhysicsWorld;
}

void dae::Scene::AddGameObject(GameObject* object)
{
	object->SetPhysicsWorld(m_pPhysicsWorld);
	m_pObjects.push_back(object);
}

const std::wstring & dae::Scene::GetSceneName() const
{
	return m_SceneName;
}

void dae::Scene::BaseUpdate()
{
	for(auto gameObject : m_pObjects)
	{
		gameObject->Update();
	}
	Update();
}

void dae::Scene::BaseRender() const
{
	for (const auto gameObject : m_pObjects)
	{
		gameObject->Render();
	}
	Render();
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
