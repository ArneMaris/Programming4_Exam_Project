#pragma once
#include <memory>
#include "TransformComponent.h"

namespace dae
{
	class Script;
	class GameObject final
	{
		friend class TransformComponent;
	public:
		virtual void Update();
		virtual void Render() const;
		virtual void Initialize();

		TransformComponent* GetTransform() const;

		void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);

		void SetPhysicsWorld(b2World* physicsWorld);
		b2World* GetPhysicsWorld();

		GameObject();
		GameObject(const std::wstring& name);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		const std::wstring& GetName() const { return m_Name; };
		void SetName(const std::wstring& newName) { m_Name = std::move(newName); };

		Script* GetScript() const;

		//Lower order = more in the background, meaning 1 will draw over 0
		void SetRenderOrder(int order) { m_RenderOrder = order; };
		int GetRenderOrder() const { return m_RenderOrder; };

		void SetLayer(int newLayer) { m_Layer = newLayer; };
		int GetLayer() const { return m_Layer; };

		void MarkForDelete() { m_NeedsDelete = true; };
		bool GetDeleteMark() { return m_NeedsDelete; };

		//leave LifeTime on zero for infinite
		void SetLifeTime(float time) { m_LifeTime = time; };

		//taken from DAE GP2 2018-2019
#pragma region 
		template <class T>
		T* GetComponent() const
		{
			const type_info& ti = typeid(T);
			for (auto component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}
			return nullptr;
		}

		template <class T>
		std::vector<T*> GetComponents() const
		{
			const type_info& ti = typeid(T);
			std::vector<T*> components;

			for (auto component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					components.push_back(static_cast<T*>(component));
			}

			return components;
		}
#pragma endregion TemplateFunctions

	protected:
		b2World* m_pPhysicsWorldRef;
	private:
		std::vector<BaseComponent*> m_pComponents;
		TransformComponent* m_TransformComp;

		bool CheckIfAlreadyHasComponent(BaseComponent* compToAdd); //add all components that where you can't have 2 of on 1 gameObject

		bool m_Initialized;
		std::wstring m_Name;
		int m_RenderOrder;
		int m_Layer;

		bool m_NeedsDelete;

		float m_LifeTime;
		float m_LifeTimer;
	};

}
