#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "SDL_scancode.h"
#include <unordered_map>

namespace dae
{

	enum class ControllerInput
	{
		NONE,
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		DpadUp = XINPUT_GAMEPAD_DPAD_UP,
		DpadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		DpadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		DpadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		ShoulderLeft = XINPUT_GAMEPAD_LEFT_SHOULDER,
		ShoulderRight = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		TriggerLeft,
		TriggerRight,
		JoyStickLeft,
		JoyStickRight
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		void CleanUp();
		void SwapInputBuffer();
		bool ProcessInput();
		dae::InputAction* AddInputAction(const std::string& name, SDL_Scancode keyBoardScanecode = SDL_SCANCODE_UNKNOWN, ControllerInput controllerInput = ControllerInput::NONE);
	private:
		XINPUT_STATE* m_CurrentGpState{};
		XINPUT_STATE* m_PreviousGpState{};
		SDL_Event* m_CurrentEvent{};
		SDL_Event* m_PreviousEvent{};

		bool IsPressed(const std::string& inputActionName);
		bool IsReleased(const std::string& inputActionName);
		bool IsHolding(const std::string& inputActionName);
		bool IsPressed(InputAction* inputActionPointer);
		bool IsReleased(InputAction* inputActionPointer);
		bool IsHolding(InputAction* inputActionPointer);

		b2Vec2 GetControllerAxis(const std::string& inputActionName); // used for triggers and joysticks
		b2Vec2 GetControllerAxis(InputAction* inputActionPointer);

		std::unordered_map <std::string, InputAction*> m_InputActions;
	};

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

			InputAction(SDL_Scancode scanCode = SDL_SCANCODE_UNKNOWN, ControllerInput button = ControllerInput::NONE);
			~InputAction() = default;

			SDL_Scancode m_ScanCode = SDL_SCANCODE_UNKNOWN;
			ControllerInput m_ControllerInput = ControllerInput::NONE;
			bool m_ControllerInputIsAxis = false;

			bool IsPressed(SDL_Event* e, SDL_Event* ePrev, XINPUT_STATE* gamePadState, XINPUT_STATE* prevGamePadState); //if pressed this frame
			bool IsReleased(SDL_Event* e, SDL_Event* ePrev, XINPUT_STATE* gamePadState, XINPUT_STATE* prevGamePadState); //if released this frame
			bool IsHolding(SDL_Event* e, SDL_Event* ePrev, XINPUT_STATE* gamePadState, XINPUT_STATE* prevGamePadState); //if holding for multiple frames
			b2Vec2 GetAxis(XINPUT_STATE* gamePadState);
			void ClampStickInput(b2Vec2& stickInput, int deadZoneValue);

			bool GetGamePadButtonDown(XINPUT_STATE gamePadState);
	};
}
