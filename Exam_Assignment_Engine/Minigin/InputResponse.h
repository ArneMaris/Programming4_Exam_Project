#pragma once
#include "GameObject.h"
#include "Response.h"

namespace dae
{
	class InputResponse : public Response
	{
	public:
		explicit InputResponse() = default;
		virtual ~InputResponse() = default;

		virtual void ExecuteOnPress() = 0;
		virtual void ExecuteOnHold(const b2Vec2 axisValues) = 0;
		virtual void ExecuteOnRelease() = 0;

		const SDL_Keycode& GetLastPressedKey() const {return m_LastKeyPressed;};
		void SetLastKeyPressed(const SDL_Keycode& keyCode) { m_LastKeyPressed = keyCode; }
		void SetOwnerObject(GameObject* newOwner) { m_pOwnerObject = newOwner; };

	protected:
		GameObject* m_pOwnerObject = nullptr;

	private:
		SDL_Keycode m_LastKeyPressed = SDLK_UNKNOWN;
	};
}

