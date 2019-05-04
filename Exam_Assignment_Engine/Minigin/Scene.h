#pragma once
#include "SceneManager.h"

class b2World;

namespace dae
{
	class GameObject;
	class Scene // temporary, this will be baseObject you make your scenes from (this class has pure viruals when finished)
	{
	public:
		void BaseUpdate(); // updates all gameObjects in this scene
		void BaseRender() const; // renders all gameObjects in this scene
		void FixedUpdate();

		virtual void Initialize() = 0;
		bool GetIsActive() const;
		void SetIsActive(bool value);
		b2World* GetPhysicsWorld() const;
		void AddGameObject(GameObject* object);
		const std::wstring& GetSceneName() const;

		Scene(const std::wstring& name, const b2Vec2& gravity = { 0, -10 });
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	protected:
		bool m_IsInitialized;
	private: 
		virtual void Update() = 0; // different Update for every scene, called in BaseUpdate
		virtual void Render() const = 0; // different Render for every scene, called in BaseRender

		virtual void OnCollisionStart() = 0;
		virtual void OnCollisionEnd() = 0;

		bool m_IsActive;
		std::wstring m_SceneName{};
		std::vector<GameObject*> m_pObjects{};

		static unsigned int s_idCounter; 
		b2World *m_pPhysicsWorld;
	};

}
