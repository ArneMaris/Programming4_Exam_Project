#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(Scene* scene);
		void RemoveScene(Scene* scene);

		void Update();
		void Render();
		void FixedUpdate();

		void CleanUp();

	private:
		std::vector<Scene*> m_pScenes;
	};

}
