#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent();
		const glm::vec3& GetPosition() const { return m_Positions; }
		void SetPosition(float x, float y, float z);
	protected:
		virtual void Update() override;
		virtual void Render() const override;
	private:
		glm::vec3 m_Positions{};
	};
}
