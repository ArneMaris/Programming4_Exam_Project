#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "SDL_keyCode.h"
#include <map>
#include "SDL_events.h"

#define MAX_CONTROLLERS 4
#define MAX_KEYS 8

namespace dae
{
	class InputAction;
	class InputComponent;

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

		void RegisterInputComponent(InputComponent* inputComp);
		void UnregisterInputComponent(InputComponent* inputComp);

		int GetAmountOfConnectedControllers();

	private:
		XINPUT_STATE m_CurrentGpState[MAX_CONTROLLERS]{};
		XINPUT_STATE m_PreviousGpState[MAX_CONTROLLERS]{};
		bool m_GamepadConnected[MAX_CONTROLLERS];
		const UINT8* m_KeyBoardState;
		UINT8 m_PrevKeyBoardState;

		std::vector<InputComponent*> m_pInputComponents;
	};


}
