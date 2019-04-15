#include "MiniginPCH.h"
#include "PhysicsComponent.h"

dae::PhysicsComponent::PhysicsComponent(SimulationType simType)
{
	switch (simType)
	{
		case SimulationType::Dynamic:

		break;
		case SimulationType::Kinematic:

			break;
		case SimulationType::Static:

			break;
	}
}

void dae::PhysicsComponent::Update()
{
}

void dae::PhysicsComponent::FixedUpdate()
{
}

