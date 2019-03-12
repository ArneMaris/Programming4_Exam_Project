#pragma once
#include <memory>

#include "TransformComponent.h"

namespace dae
{
	class GameObject
	{
	public:
		virtual void Update() = 0;
		virtual void Render() const = 0;

		//template<T>
		//void AddComponent<T>

		void SetPosition(float x, float y);
		const glm::vec3 GetPosition();
		TransformComponent* GetTransform() const { return m_pTransform; }

		void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:

	private:
		TransformComponent* m_pTransform;
		std::vector<BaseComponent*> m_pComponents;
	};
}
