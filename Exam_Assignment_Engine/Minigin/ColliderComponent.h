#pragma once
#include "BaseComponent.h"

namespace dae
{
	class ColliderComponent :public BaseComponent
	{
	public:
		explicit ColliderComponent();
		virtual ~ColliderComponent() = default;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

	protected:
		virtual void Update() override;
	};

}
