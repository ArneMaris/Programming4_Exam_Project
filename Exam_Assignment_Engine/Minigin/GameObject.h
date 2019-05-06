#pragma once
#include <memory>
#include "TransformComponent.h"

namespace dae
{
	class GameObject final
	{
	public:
		virtual void Update();
		virtual void Render() const;
		virtual void Initialize();

		TransformComponent* GetTransform() const;

		BaseComponent* AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);

		void SetPhysicsWorld(b2World* physicsWorld);
		b2World* GetPhysicsWorld();

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//taken from DAE GP2 2018-2019
#pragma region 
		template <class T>
		T* GetComponent()
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
		std::vector<T*> GetComponents()
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

		bool m_Initialized;
	};

}
