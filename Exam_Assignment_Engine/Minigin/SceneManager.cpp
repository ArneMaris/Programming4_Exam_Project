#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update()
{
	for(auto scene : m_pScenes)
	{
		if (scene->GetIsActive())
			scene->BaseUpdate();
	}
}

void dae::SceneManager::FixedUpdate()
{
	for (auto scene : m_pScenes)
	{
		if (scene->GetIsActive())
			scene->BaseUpdate();
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : m_pScenes)
	{
		if (scene->GetIsActive())
			scene->BaseRender();
	}
}

void dae::SceneManager::CleanUp()
{
	for (std::vector<Scene*>::iterator it = m_pScenes.begin(); it != m_pScenes.end(); ++it)
	{
		(*it)->~Scene();
		delete (*it);
	}
	m_pScenes.clear();
}


void dae::SceneManager::AddScene(Scene* scene)
{
	m_pScenes.push_back(scene);
}
void dae::SceneManager::RemoveScene(Scene* scene)
{
	auto it = find(m_pScenes.begin(), m_pScenes.end(), scene);
	m_pScenes.erase(it);
}
