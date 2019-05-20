#pragma once
#include "Response.h"

namespace dae
{
	class GameObject;
	class InputResponse : public Response
	{
	public:
		explicit InputResponse() = default;
		virtual ~InputResponse() = default;

		InputResponse(const InputResponse& other) = delete;
		InputResponse(InputResponse&& other) = delete;
		InputResponse& operator=(const InputResponse& other) = delete;
		InputResponse& operator=(InputResponse&& other) = delete;

		virtual void ExecuteOnPress() = 0;
		virtual void ExecuteOnHold(const b2Vec2 axisValues) = 0;
		virtual void ExecuteOnRelease() = 0;

		// you dont have to do this, it will be automatically done when you add it on a component (gameobject of that component)
		// this is just here in case you need to change it runtime (probably never)
		void SetOwnerObject(GameObject* newOwner) { m_pOwnerObject = newOwner; };

	protected:
		GameObject* m_pOwnerObject = nullptr;
	};
}

