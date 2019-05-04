#pragma once
#include "BaseComponent.h"

namespace dae
{
	class PhysicsBodyComponent final: public BaseComponent
	{
	public:
		PhysicsBodyComponent(b2BodyType bodyType = b2BodyType::b2_staticBody); //super easy constructer that also has default param, in other words can be called without 
										//params to make a default static body at position {0.0}, rotation 0, mass 1, active = true;
		PhysicsBodyComponent(b2BodyType bodyType, const b2Vec2& pos, const float rotRadians, float linearDamping = 0.01f, float angularDamping = 0.01f, bool startActive = true, bool isFastTraveling = false);

		// only use this if you know what ur doing with box2D
		b2Body* GetPhysicsBody() const;

		~PhysicsBodyComponent() = default;
		PhysicsBodyComponent(const PhysicsBodyComponent& other) = delete;
		PhysicsBodyComponent(PhysicsBodyComponent&& other) = delete;
		PhysicsBodyComponent& operator=(const PhysicsBodyComponent& other) = delete;
		PhysicsBodyComponent& operator=(PhysicsBodyComponent&& other) = delete;

		virtual void Update() override;

	private:
		b2World* m_pPhysicsWorldRef;
		b2Body* m_Body;
	};
}

