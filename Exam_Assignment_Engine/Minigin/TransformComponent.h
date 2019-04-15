#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent();
		const b2Vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z = 1);
	protected:
		virtual void Update() override;
	private:
		b2Vec3 m_Position{};
	};
}
