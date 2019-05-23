#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Initialize()
{
	for (const auto& scene : m_pScenes)
	{
		if (!scene->IsInitialized())
		{
			m_InitializingScene = scene;
			scene->PreparePhysics();
			scene->Initialize();
			scene->ActivateGameObjects();
		}
	}
	if (m_GlobalScene != nullptr)
	{
		m_InitializingScene = m_GlobalScene;
		m_GlobalScene->Initialize();
		m_GlobalScene->ActivateGameObjects();
	}
	m_InitializingScene = nullptr;
}

void dae::SceneManager::Update()
{  
	for(const auto& scene : m_pScenes)
	{
		if (scene->GetIsActive())
			scene->BaseUpdate();
	}
	if (m_GlobalScene != nullptr)
	{
		m_GlobalScene->BaseUpdate();
	}
}

void dae::SceneManager::Render()
{
	if (!m_RenderGlobalSceneFront)
	{
		if (m_GlobalScene != nullptr)
		{
			m_GlobalScene->BaseRender();
		}
		for (const auto& scene : m_pScenes)
		{
			if (scene->GetIsActive())
				scene->BaseRender();
		}
	}
	else
	{
		for (const auto& scene : m_pScenes)
		{
			if (scene->GetIsActive())
				scene->BaseRender();
		}
		if (m_GlobalScene != nullptr)
		{
			m_GlobalScene->BaseRender();
		}
	}
}

void dae::SceneManager::FixedUpdate()
{
	for (const auto& scene : m_pScenes)
	{
		if (scene->GetIsActive())
			scene->FixedUpdate();
	}
}

void dae::SceneManager::CheckDeleteMarkings()
{
	for (const auto& scene : m_pScenes)
	{
		if (scene->GetIsActive())
			scene->CheckDeleteMarkings();
	}
	if (m_GlobalScene != nullptr)
	{
		m_GlobalScene->CheckDeleteMarkings();
	}
}

void dae::SceneManager::ReloadActiveScene()
{
	GetActiveScene()->CleanAndReload();
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
	delete m_GlobalScene;

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
	if (m_InitializingScene != nullptr)
		return m_InitializingScene;
	else
	{
		for (size_t i = 0; i < m_pScenes.size(); i++)
		{
			if (m_pScenes[i]->GetIsActive() == true)
			{
				return m_pScenes[i];
			}
		}
	}
	//Logger::GetInstance().LogWarning(L"No active scenes found!");
	return nullptr;
}

void dae::SceneManager::SetActiveScene(const std::wstring & sceneName)
{
	for (size_t i = 0; i < m_pScenes.size(); i++)
	{
		if (m_pScenes[i]->GetSceneName() == sceneName)
		{
			GetActiveScene()->CleanAndReload();
			m_pScenes[i]->SetIsActive(true);
			return;
		}
	}
	Logger::GetInstance().LogWarning(L"Scene with name: " + sceneName + L" not found, have you added it to the sceneManager?");
}

void dae::SceneManager::SetNextSceneActive()
{
	for (size_t i = 0; i < m_pScenes.size(); i++)
	{
		if (m_pScenes[i]->GetIsActive() == true)
		{
			m_pScenes[i]->SetIsActive(false);
			m_pScenes[i]->CleanAndReload();
			if (i + 1 < m_pScenes.size())
				m_pScenes[i + 1]->SetIsActive(true);
			else
				m_pScenes[0]->SetIsActive(true);

			break;
		}
	}
}

void dae::SceneManager::SetPreviousSceneActive()
{
	for (size_t i = 0; i < m_pScenes.size(); i++)
	{
		if (m_pScenes[i]->GetIsActive() == true)
		{
			m_pScenes[i]->SetIsActive(false);
			m_pScenes[i]->CleanAndReload();
			if (i - 1 > 0)
				m_pScenes[i - 1]->SetIsActive(true);
			else 
				m_pScenes[m_pScenes.size()-1]->SetIsActive(true);

			break;
		}
	}
}
