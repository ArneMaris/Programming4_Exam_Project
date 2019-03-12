#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::s_idCounter = 0;

dae::Scene::Scene(const std::string& name) 
	:m_SceneName(name)
{
}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_pObjects.push_back(object);
}

void dae::Scene::Update()
{
	for(auto gameObject : m_pObjects)
	{
		gameObject->Update();
	}
}

void dae::Scene::Render() const
{
	for (const auto gameObject : m_pObjects)
	{
		gameObject->Render();
	}
}

