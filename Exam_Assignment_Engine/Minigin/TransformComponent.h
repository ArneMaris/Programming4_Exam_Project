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
		glm::vec3 m_Positions;
	public:
		const glm::vec3& GetPosition() const { return m_Positions; }
		void SetPosition(float x, float y, float z);
	};
}
