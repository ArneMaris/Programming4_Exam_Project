#pragma once
#include "BaseComponent.h"

namespace dae
{
	class PhysicsComponent : public BaseComponent
	{
	public:
		enum SimulationType
		{
			Dynamic,
			Kinematic,
			Static
		};
		explicit PhysicsComponent(SimulationType simType);
		virtual ~PhysicsComponent() = default;
		PhysicsComponent(const PhysicsComponent& other) = delete;
		PhysicsComponent(PhysicsComponent&& other) = delete;
		PhysicsComponent& operator=(const PhysicsComponent& other) = delete;
		PhysicsComponent& operator=(PhysicsComponent&& other) = delete;

	protected:
		virtual void Update() override;
		virtual void FixedUpdate() override;
	private:
	};
}
