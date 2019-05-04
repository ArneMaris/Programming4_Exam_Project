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

		void Initialize();
		void Update();
		void Render();
		void FixedUpdate();

		b2World* GetPhysicsWorld();

		void CleanUp();

	private:
		std::vector<Scene*> m_pScenes;
	};

}
