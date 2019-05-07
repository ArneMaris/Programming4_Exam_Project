#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Initialize()
{
	for (auto scene : m_pScenes)
	{
		scene->Initialize();
		scene->ActivateGameObjects();
	}
}

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

b2World* dae::SceneManager::GetPhysicsWorld()
{
	return GetActiveScene()->GetPhysicsWorld();
}

void dae::SceneManager::CleanUp()
{
	for (auto it = m_pScenes.begin(); it != m_pScenes.end(); ++it)
	{
		delete (*it);
	}
	m_pScenes.clear();
}

void dae::SceneManager::AddScene(Scene* scene, bool setActive)
{
	m_pScenes.push_back(scene);
	if (setActive)
		scene->SetIsActive(true);
	else
		scene->SetIsActive(false);
}
void dae::SceneManager::RemoveScene(Scene* scene)
{
	auto it = find(m_pScenes.begin(), m_pScenes.end(), scene);
	m_pScenes.erase(it);
}

dae::Scene* dae::SceneManager::GetActiveScene()
{
	for (size_t i = 0; i < m_pScenes.size(); i++)
	{
		if (m_pScenes[i]->GetIsActive() == true)
		{
			return m_pScenes[i];
		}
	}
	Logger::GetInstance().LogWarning(L"No active scenes found!");
	return nullptr;
}

void dae::SceneManager::SetActiveScene(const std::wstring & sceneName)
{
	for (size_t i = 0; i < m_pScenes.size(); i++)
	{
		if (m_pScenes[i]->GetSceneName() == sceneName)
		{
			m_pScenes[i]->SetIsActive(true);
			return;
		}
	}
	Logger::GetInstance().LogWarning(L"Scene with name: " + sceneName + L" not found, have you added it to the sceneManager?");
}
