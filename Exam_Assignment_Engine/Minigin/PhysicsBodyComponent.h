#pragma once
#include "BaseComponent.h"

namespace dae
{

	class PhysicsBodyComponent : public BaseComponent
	{
	public:
		PhysicsBodyComponent(b2BodyType bodyType = b2BodyType::b2_staticBody); //super easy constructer that also has default param, in other words can be called without 
										//params to make a default static body at position {0.0}, rotation 0, mass 1, active = true;
		PhysicsBodyComponent(b2BodyType bodyType, const b2Vec2& pos, const float rotRad, float linearDamping = 0.01f, float angularDamping = 0.01f, bool startActive = true, bool isFastTraveling = false);

		void AddCollisionShape(b2Shape* shape);
		void AddCollisionShape(b2Shape* shape, bool isSensor);
		void AddCollisionShape(b2Shape* shape, bool isSensor, float density, float friction, float restitution);

		// only use this if you know what ur doing with box2D
		b2Body* GetPhysicsBody() const;
		b2Fixture* GetFixture() const;

		~PhysicsBodyComponent() = default;
		PhysicsBodyComponent(const PhysicsBodyComponent& other) = delete;
		PhysicsBodyComponent(PhysicsBodyComponent&& other) = delete;
		PhysicsBodyComponent& operator=(const PhysicsBodyComponent& other) = delete;
		PhysicsBodyComponent& operator=(PhysicsBodyComponent&& other) = delete;
	private:
		b2World* m_pPhysicsWorldRef;
		b2Body* m_Body;
		b2Fixture* m_Fixture;
	};
}

