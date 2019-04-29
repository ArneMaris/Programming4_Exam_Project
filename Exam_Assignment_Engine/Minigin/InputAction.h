#pragma once
#include "SDL_Scancode.h"
#include "InputManager.h"

namespace dae
{
	class InputAction final //a single inputAction that you can put into the InputManager that will return if this inputAction is true or false
	{
		friend class InputManager;
	private:
		enum class ControllerAxis
		{
			NONE,
			StickLeft,
			StickRight,
			TriggerLeft,
			TriggerRight
		};
	
		InputAction(SDL_Scancode scanCode = SDL_SCANCODE_UNKNOWN, dae::ControllerInput button = dae::ControllerInput::NONE);
		~InputAction() = default;

		//InputAction(const InputAction& InputAction) = delete;
		//InputAction(InputAction&& InputAction) = delete;
		//InputAction& operator=(const InputAction& other) = delete;
		//InputAction& operator=(InputAction&& other) = delete;

		SDL_Scancode m_ScanCode = SDL_SCANCODE_UNKNOWN;
		dae::ControllerInput m_ControllerInput = dae::ControllerInput::NONE;
		bool m_ControllerInputIsAxis = false;

		bool IsPressed(SDL_Event* e, SDL_Event* ePrev, XINPUT_STATE* gamePadState, XINPUT_STATE* prevGamePadState); //if pressed this frame
		bool IsReleased(SDL_Event* e, SDL_Event* ePrev, XINPUT_STATE* gamePadState, XINPUT_STATE* prevGamePadState); //if released this frame
		bool IsHolding(SDL_Event* e, SDL_Event* ePrev, XINPUT_STATE* gamePadState, XINPUT_STATE* prevGamePadState); //if holding for multiple frames
		b2Vec2 GetAxis(XINPUT_STATE* gamePadState);
		void ClampStickInput(b2Vec2& stickInput, int deadZoneValue);
	};
}

