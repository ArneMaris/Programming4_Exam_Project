#pragma once
#include "BaseComponent.h"

namespace dae
{
	class PhysicsBodyComponent final: public BaseComponent
	{
	public:
		PhysicsBodyComponent(b2BodyType bodyType = b2BodyType::b2_staticBody, bool enableRotation = false); //super easy constructer that also has default param, in other words can be called without 
										//params to make a default static body at position {0.0}, rotation 0, mass 1, active = true;
		PhysicsBodyComponent(b2BodyType bodyType, bool enableRotation, const b2Vec2& pos, const float rotRadians, float linearDamping = 0.01f, float angularDamping = 0.01f, bool startActive = true, bool isFastTraveling = false);

		// only use this if you know what ur doing with box2D
		b2Body* GetPhysicsBody() const;

		~PhysicsBodyComponent() {m_Body->SetUserData(nullptr);};
		PhysicsBodyComponent(const PhysicsBodyComponent& other) = delete;
		PhysicsBodyComponent(PhysicsBodyComponent&& other) = delete;
		PhysicsBodyComponent& operator=(const PhysicsBodyComponent& other) = delete;
		PhysicsBodyComponent& operator=(PhysicsBodyComponent&& other) = delete;

		void ApplyForce(const b2Vec2& force, const b2Vec2& point);
		void ApplyTorque(float torque);
		void ApplyLinearImpulse(const b2Vec2& impulse, const b2Vec2& point);
		void ApplyAngularImpulse(float impulse);
		void SetLinearVelocity(const b2Vec2& vel);
		void SetAngularVelocity(float angularVel);

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;

	private:
		b2World* m_pPhysicsWorldRef;
		b2Body* m_Body;
	};
}

