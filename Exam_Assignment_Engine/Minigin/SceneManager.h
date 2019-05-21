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

		Scene* GetActiveScene();
		void SetActiveScene(const std::wstring& sceneName);

		void SetNextSceneActive();
		void SetPreviousSceneActive();

		void Initialize();
		void Update();
		void Render();
		void FixedUpdate();

		void SetReloaded() { m_Reloading = false; };

		void ReloadActiveScene();

		b2World* GetPhysicsWorld();

		void CleanUp();

	private:
		bool m_Reloading = false;
		std::vector<Scene*> m_pScenes;
	};

}
