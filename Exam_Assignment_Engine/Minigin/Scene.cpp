#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::s_idCounter = 0;

dae::Scene::Scene(const std::string& name, bool startActive) 
	:m_SceneName(name)
	, m_IsActive{ startActive }
{
}

dae::Scene::~Scene()
{
	for (std::vector<GameObject*>::iterator it = m_pObjects.begin(); it != m_pObjects.end(); ++it)
	{
		delete (*it);
	}
	m_pObjects.clear();
}

void dae::Scene::AddGameObject(GameObject* object)
{
	m_pObjects.push_back(object);
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

bool dae::Scene::GetIsActive() const
{
	return m_IsActive;
}

void dae::Scene::SetIsActive(bool value)
{
	m_IsActive = value;
}

