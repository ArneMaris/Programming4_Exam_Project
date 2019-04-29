#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "SDL_scancode.h"
#include <map>


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
		bool IsPressed(const std::wstring& inputActionName);
		bool IsReleased(const std::wstring& inputActionName);
		bool IsHolding(const std::wstring& inputActionName);
		bool IsPressed(InputAction* inputActionPointer);
		bool IsReleased(InputAction* inputActionPointer);
		bool IsHolding(InputAction* inputActionPointer);

		b2Vec2 GetControllerAxis(const std::wstring& inputActionName); // used for triggers and joysticks
		b2Vec2 GetControllerAxis(dae::InputAction* inputActionPointer);
	private:
		XINPUT_STATE* m_CurrentGpState{};
		XINPUT_STATE* m_PreviousGpState{};
		SDL_Event* m_CurrentEvent{};
		SDL_Event* m_PreviousEvent{};
		std::map<const std::wstring, dae::InputAction*> m_InputActions{};
	};


}
