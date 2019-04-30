#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "SDL_scancode.h"
#include <map>

#define MAX_CONTROLLERS 4;

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

		InputAction* AddInputAction(const std::wstring& name);
		InputAction* AddInputAction(const std::wstring& name, SDL_Scancode keyBoardScanecode, ControllerInput controllerInput);
		InputAction* AddInputAction(const std::wstring& name, SDL_Scancode keyBoardScanecode);
		InputAction* AddInputAction(const std::wstring& name, ControllerInput controllerInput);
		bool IsPressed(const std::wstring& inputActionName, unsigned int controllerId);
		bool IsReleased(const std::wstring& inputActionName, unsigned int controllerId);
		bool IsHolding(const std::wstring& inputActionName, unsigned int controllerId);
		bool IsPressed(InputAction* inputActionPointer, unsigned int controllerId);
		bool IsReleased(InputAction* inputActionPointer, unsigned int controllerId);
		bool IsHolding(InputAction* inputActionPointer, unsigned int controllerId);

		b2Vec2 GetControllerAxis(const std::wstring& inputActionName, unsigned int controllerId); // used for triggers and joysticks
		b2Vec2 GetControllerAxis(InputAction* inputActionPointer, unsigned int controllerId);
	private:
		XINPUT_STATE* m_CurrentGpState[4]{};
		XINPUT_STATE* m_PreviousGpState[4]{};
		SDL_Event* m_CurrentEvent{};
		SDL_Event* m_PreviousEvent{};
		std::map<const std::wstring, InputAction*> m_InputActions{};
	};


}
