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
		float GetRotation() const { return m_Rotation; }
		void SetPosition(float x, float y);
		void SetRotation(float rotInRadians);
		void SetPosition(const b2Vec2& pos);

		void Translate(float x, float y);
		void Translate(const b2Vec2& pos);

		void Rotate(float angleInRadians);
	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;
	private:
		TransformComponent();
		b2Vec2 m_Position{};
		float m_Rotation;

		b2Body* m_pPhysicsBody;
	};
}
