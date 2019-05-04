#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(std::shared_ptr<Scene> scene);
		void RemoveScene(std::shared_ptr<Scene> scene);

		void Update();
		void Render();
		void FixedUpdate();

		void CleanUp();

	private:
		std::vector<std::shared_ptr<Scene>> m_pScenes;
	};

}
