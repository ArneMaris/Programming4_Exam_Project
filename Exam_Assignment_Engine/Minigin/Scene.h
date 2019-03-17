#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene // temporary, this will be baseObject you make your scenes from (this class has pure viruals when finished)
	{
	public:
		void BaseUpdate();
		void BaseRender() const;
		virtual void Initialize() = 0;
		bool GetIsActive() const;
		void SetIsActive(bool value);
		void AddGameObject(GameObject* object);

		Scene(const std::string& name, bool autoActivate = true);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	private: 
		virtual void Update() = 0;
		virtual void Render() const = 0;
		bool m_IsActive;
		std::string m_SceneName{};
		std::vector <GameObject*> m_pObjects{};

		static unsigned int s_idCounter; 
	};

}
