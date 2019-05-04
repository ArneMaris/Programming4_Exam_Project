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

void dae::SceneManager::Render()
{
	for (const auto scene : m_pScenes)
	{
		if (scene->GetIsActive())
			scene->BaseRender();
	}
}

void dae::SceneManager::FixedUpdate()
{
	for (const auto scene : m_pScenes)
	{
		if (scene->GetIsActive())
			scene->FixedUpdate();
	}
}

void dae::SceneManager::CleanUp()
{
	m_pScenes.clear();
}


void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_pScenes.push_back(scene);
}
void dae::SceneManager::RemoveScene(std::shared_ptr<Scene> scene)
{
	auto it = find(m_pScenes.begin(), m_pScenes.end(), scene);
	m_pScenes.erase(it);
}
