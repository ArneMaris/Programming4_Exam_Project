#pragma once
#include "GameObject.h"

namespace dae
{
	class InputResponse
	{
	public:
		InputResponse() = default;
		virtual ~InputResponse() = default;

		virtual void ExecuteOnPress() = 0;
		virtual void ExecuteOnHold(const b2Vec2 axisValues) = 0;
		virtual void ExecuteOnRelease() = 0;

		void SetOwnerObject(GameObject* newOwner) { m_pOwnerObject = newOwner; };

	protected:
		GameObject* m_pOwnerObject = nullptr;
	};
}

