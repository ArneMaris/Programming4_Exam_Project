#pragma once
#include "SceneManager.h"

class b2World;

namespace dae
{
	class GridLevel;
	class GameObject;
	class Prefab;
	class Scene // temporary, this will be baseObject you make your scenes from (this class has pure viruals when finished)
	{
	public:
		void BaseUpdate(); // updates all gameObjects in this scene
		void BaseRender() const; // renders all gameObjects in this scene
		void FixedUpdate();

		virtual void Initialize() = 0;
		void ActivateGameObjects();

		bool GetIsActive() const;
		void SetIsActive(bool value);
		b2World* GetPhysicsWorld() const;
		void AddGameObject(GameObject* object);
		void AddGameObject(Prefab* object);

		void AddLevel(GridLevel* level);
		const std::wstring& GetSceneName() const;

		Scene(const std::wstring& name, const b2Vec2& gravity = { 0, -10 });
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void EnablePhysicsDebugDrawing() { GameInfo::drawPhysicsDebug = true; };
		void DisablePhysicsDebugDrawing() { GameInfo::drawPhysicsDebug = false; };

		GameObject* GetGameObject(const std::wstring& name);

		void SortRenderingOrder();

	protected:
		bool m_IsInitialized;
		std::vector<GridLevel*> m_pLevels;

	private: 
		virtual void Update() = 0; // different Update for every scene, called in BaseUpdate
		virtual void Render() const = 0; // different Render for every scene, called in BaseRender

		bool m_IsActive;
		std::wstring m_SceneName{};
		std::vector<GameObject*> m_pObjects{};

		b2World *m_pPhysicsWorld;
		b2ContactListener* m_MMCallbacks;


	};

}
