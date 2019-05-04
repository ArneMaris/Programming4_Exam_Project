#include "MiniginPCH.h"
#include "InputAction.h"
#include "SDL_events.h"


dae::InputAction::InputAction(SDL_Scancode scanCode, ControllerInput controllerInput)
	:m_ControllerInputIsAxis{false}
{
	m_ScanCode = scanCode;
	m_ControllerInput = controllerInput;
	switch (m_ControllerInput)
	{
	case ControllerInput::JoyStickLeft:
	case ControllerInput::JoyStickRight:
	case ControllerInput::ShoulderLeft:
	case ControllerInput::ShoulderRight:
		m_ControllerInputIsAxis = true;
		break;
	}
}

bool dae::InputAction::IsPressed(SDL_Event& e, SDL_Event& ePrev, XINPUT_STATE& gamePadState, XINPUT_STATE& prevGamePadState)
{
	//KEYBOARD INPUT
	if (m_ScanCode != SDL_SCANCODE_UNKNOWN)
	{
		if (e.key.keysym.scancode == m_ScanCode && ePrev.key.keysym.scancode != m_ScanCode) // if now is true and prev is false key is just pressed
			return true;
	}

	//CONTROLLER INPUT
	if (!m_ControllerInputIsAxis)
	{
		if (gamePadState.Gamepad.wButtons == DWORD(m_ControllerInput) && prevGamePadState.Gamepad.wButtons != DWORD(m_ControllerInput))
			return true;
	}
	else
	{
		Logger::LogWarning(L"Trying to get Axis value from IsPressed(), this works only for buttons and will now returns false, use GetControllerAxis() instead!");
		return false;
	}
	return false;
}

bool dae::InputAction::IsReleased(SDL_Event& e, SDL_Event& ePrev, XINPUT_STATE& gamePadState, XINPUT_STATE& prevGamePadState)
{
	//KEYBOARD INPUT
	if (m_ScanCode != SDL_SCANCODE_UNKNOWN)
	{
		if (e.key.keysym.scancode != m_ScanCode && ePrev.key.keysym.scancode == m_ScanCode) // if now is false and prev is true key is just released
			return true;
	}

	//CONTROLLER INPUT
	if (!m_ControllerInputIsAxis)
	{
		if (gamePadState.Gamepad.wButtons != DWORD(m_ControllerInput) && prevGamePadState.Gamepad.wButtons == DWORD(m_ControllerInput))
			return true;
	}
	else
	{
		Logger::LogWarning(L"Trying to get Axis value from IsReleased(), this works only for buttons and will now returns false, use GetControllerAxis() instead!");
		return false;
	}
	return false;
}

bool dae::InputAction::IsHolding(SDL_Event& e, SDL_Event& ePrev, XINPUT_STATE& gamePadState, XINPUT_STATE& prevGamePadState)
{
	//KEYBOARD INPUT
	if (m_ScanCode != SDL_SCANCODE_UNKNOWN)
	{
		if (e.key.keysym.scancode == m_ScanCode && ePrev.key.keysym.scancode == m_ScanCode) //if both prev and now is true means button is being held
			return true;
	}

	//CONTROLLER INPUT
	if (!m_ControllerInputIsAxis)
	{
		if (gamePadState.Gamepad.wButtons == DWORD(m_ControllerInput) && prevGamePadState.Gamepad.wButtons == DWORD(m_ControllerInput))
			return true;
	}
	else
	{
		Logger::LogWarning(L"Trying to get Axis value from IsHolding(), this works only for buttons and will now returns false, use GetControllerAxis() instead!");
		return false;
	}

	return false;
}

b2Vec2 dae::InputAction::GetAxis(XINPUT_STATE& gamePadState)
{
	b2Vec2 stickInput{ 0,0 };
	switch (m_ControllerInput)
	{
	case ControllerInput::JoyStickLeft:
		stickInput = { float32(gamePadState.Gamepad.sThumbLX), float32(gamePadState.Gamepad.sThumbLY) };
		ClampStickInput(stickInput, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	case ControllerInput::JoyStickRight:
		stickInput = { float32(gamePadState.Gamepad.sThumbRX), float32(gamePadState.Gamepad.sThumbRY) };
		ClampStickInput(stickInput, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		break;
	case ControllerInput::TriggerLeft:
		stickInput = { (int(gamePadState.Gamepad.bLeftTrigger) / 255.0f), 0 };
		break;
	case ControllerInput::TriggerRight:
		stickInput = { (int(gamePadState.Gamepad.bRightTrigger) / 255.0f), 0 };
		break;
	default:
		Logger::LogWarning(L"Trying to do GetAxis() on a button, this only works on JoySticks and Triggers, will now return {0,0}");
		break;
	}
	return stickInput;
}

void dae::InputAction::ClampStickInput(b2Vec2 & stickInput, int deadZoneValue)
{
	//determine how far the controller is pushed
	float magnitude = sqrt(stickInput.x*stickInput.x + stickInput.y * stickInput.y);

	//determine the direction the controller is pushed
	float normalizedLX = stickInput.x / magnitude;
	float normalizedLY = stickInput.y / magnitude;

	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > deadZoneValue)
	{
		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - deadZoneValue);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		normalizedMagnitude = 0.0;
	}
	stickInput = { normalizedMagnitude * normalizedLX, normalizedMagnitude * normalizedLY };
}
