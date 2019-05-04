#pragma once
#include <string>
#include "Box2D/Common/b2Math.h"

namespace dae
{
	class GameObject;
	class TransformComponent;

	class BaseComponent
	{
		friend class GameObject;
	public:
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		virtual ~BaseComponent() =default;
		BaseComponent() = default;

		std::shared_ptr<GameObject> GetGameObject() const { return m_pGameObject; }
		std::shared_ptr<TransformComponent> GetTransform() const;

	protected:
		virtual void Update() = 0;
		virtual void Render() const;

		std::shared_ptr<GameObject> m_pGameObject;
	};
};

