#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "SDL_keyCode.h"
#include <map>
#include "SDL_events.h"
#include "Command.h"

#define MAX_CONTROLLERS 4

namespace dae
{
	class InputAction;

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

		void AddInputAction(Command* command, SDL_Keycode keyBoardScanecode, ControllerInput controllerInput, int controllerId);
		void AddInputAction(Command* command, SDL_Keycode keyBoardScanecode);
		void AddInputAction(Command* command, ControllerInput controllerInput, int controllerId);

	private:
		XINPUT_STATE m_CurrentGpState[MAX_CONTROLLERS]{};
		XINPUT_STATE m_PreviousGpState[MAX_CONTROLLERS]{};
		bool m_GamepadConnected[MAX_CONTROLLERS];
		SDL_Event m_CurrentEvent;
		std::map<int, InputAction*> m_InputActions; //int here is the controller ID, -1 if no controller input but keyboard input only
	};


}
