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
		virtual void FixedUpdate();

		void SetPosition(float x, float y);
		const b2Vec3 GetPosition();
		TransformComponent* GetTransform() const { return m_pTransform; }

		void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);

		GameObject();
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

#pragma region
		template <class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_pComponents)
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

			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					components.push_back(static_cast<T*>(component));
			}

			return components;
		}
#pragma endregion TemplateFunctions

	protected:

	private:
		TransformComponent* m_pTransform;
		std::vector<BaseComponent*> m_pComponents;
	};

}
