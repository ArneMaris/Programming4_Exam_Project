#pragma once
#include "SDL_keyCode.h"
#include "InputManager.h"

namespace dae
{
	class InputResponse;
	class InputAction final //a single inputAction that you can put into the InputManager that will return if this inputAction is true or false
	{
		friend class InputComponent;
	private:
		enum class ControllerAxis
		{
			NONE,
			StickLeft,
			StickRight,
			TriggerLeft,
			TriggerRight
		};
	
		InputAction(InputResponse* response, SDL_Keycode keyCode = SDLK_UNKNOWN, dae::ControllerInput button = dae::ControllerInput::NONE);
		~InputAction();

		InputAction(const InputAction& InputAction) = delete;
		InputAction(InputAction&& InputAction) = delete;
		InputAction& operator=(const InputAction& other) = delete;
		InputAction& operator=(InputAction&& other) = delete;

		SDL_Keycode m_KeyCode = SDLK_UNKNOWN;
		dae::ControllerInput m_ControllerInput = dae::ControllerInput::NONE;
		bool m_ControllerInputIsAxis = false;
		bool m_KeyHeld = false;

		void HandleKeyBoardInput(SDL_Event& e); //if pressed this frame
		void HandleControllerInput(XINPUT_STATE& gamePadState, XINPUT_STATE& prevGamePadState); //if pressed this frame
		b2Vec2 GetAxis(XINPUT_STATE& gamePadState);
		void ClampStickInput(b2Vec2& stickInput, int deadZoneValue);

		InputResponse* GetResponse() const {return m_pResponse;};

		InputResponse* m_pResponse;
	};
}

