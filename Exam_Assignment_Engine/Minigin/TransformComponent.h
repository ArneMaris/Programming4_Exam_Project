#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent();
		const b2Vec2& GetPosition() const { return m_Position; }
		float GetRotation() const { return m_Rotation; }
		void SetPosition(float x, float y);
		void SetRotation(float rot);
		void SetPosition(const b2Vec2& pos);

		void Translate(float x, float y);
		void Translate(b2Vec2& pos);

		void Rotate(float angle);
	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;
	private:
		b2Vec2 m_Position{};
		float m_Rotation;
	};
}
