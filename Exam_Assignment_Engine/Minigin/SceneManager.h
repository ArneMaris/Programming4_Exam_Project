#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(Scene* scene, bool setActive = true);
		void RemoveScene(Scene* scene);

		//Global scene = scene that is always active and stays during the whole duration of the application (example: menu)
		void AddGlobalScene(Scene* scene) { m_GlobalScene = scene; };
		Scene* GetGlobalScene() const {return m_GlobalScene; };
		void SetGlobalSceneRenderFront(bool value) { m_RenderGlobalSceneFront = value; }

		Scene* GetActiveScene();
		void SetActiveScene(const std::wstring& sceneName);

		void SetNextSceneActive();
		void SetPreviousSceneActive();

		void Initialize();
		void Update();
		void Render();
		void FixedUpdate();
		void CheckDeleteMarkings();

		void SetReloaded() { m_Reloading = false; };

		void ReloadActiveScene();

		b2World* GetPhysicsWorld();

		void CleanUp();

	private:
		bool m_Reloading = false;
		std::vector<Scene*> m_pScenes;
		Scene* m_GlobalScene = nullptr;
		bool m_RenderGlobalSceneFront = false;

		Scene* m_InitializingScene = nullptr;
	};

}
