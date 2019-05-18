#pragma once
#include "BaseComponent.h"

namespace dae
{
	class PhysicsBodyComponent;
	class TransformComponent final : public BaseComponent
	{
		friend class GameObject;
	public:
		const b2Vec2& GetPosition() const { return m_Position; }
		float GetRotationDegrees() const { return m_Rotation; }
		float GetRotationRadians() const { return DegreesToRad(m_Rotation); }
		void SetPosition(float x, float y);
		void SetRotation(float rotInDegrees);
		void SetPosition(const b2Vec2& pos);

		void Translate(float x, float y);
		void Translate(const b2Vec2& pos);

		bool MoveToPosition(const b2Vec2& pos, float speed, bool force = false);

		void Rotate(float rotInDegrees);
	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;
	private:
		TransformComponent();
		b2Vec2 m_Position{};

		//IN DEGREES!!!
		float m_Rotation;

		b2Body* m_pPhysicsBody;

		b2Vec2 m_TargetPos;
		float m_TargetSeekSpeed;
		bool m_Seeking;
	};
}
