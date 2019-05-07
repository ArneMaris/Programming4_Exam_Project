#include "MiniginPCH.h"
#include "InputAction.h"
#include "SDL_events.h"


dae::InputAction::InputAction(Command* command, SDL_Keycode keyCode, ControllerInput controllerInput)
	:m_ControllerInputIsAxis{false}
	,m_Command { command }
{
	m_KeyCode = keyCode;
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

void dae::InputAction::HandleInput(SDL_Event& e, XINPUT_STATE& gamePadState, XINPUT_STATE& prevGamePadState, bool gamePadConnected)
{
	//KEYBOARD INPUT
	if (m_KeyCode != SDLK_UNKNOWN)
	{
		if (e.key.keysym.sym == m_KeyCode && e.type == SDL_KEYDOWN) // if now is true and prev is false key is just pressed
		{
			m_Command->ExecuteOnPress(); 
			m_KeyHeld = true;
		}
		else if (e.key.keysym.sym == m_KeyCode && e.type == SDL_KEYUP)
		{
			m_Command->ExecuteOnRelease();
			m_KeyHeld = false;
		}
		else if (m_KeyHeld)
		{
			m_Command->ExecuteOnHold({ 0,0 });
		}
	}

	//CONTROLLER INPUT
	if (!m_ControllerInputIsAxis && gamePadConnected && m_ControllerInput != ControllerInput::NONE)
	{
		if (gamePadState.Gamepad.wButtons == DWORD(m_ControllerInput) && prevGamePadState.Gamepad.wButtons != DWORD(m_ControllerInput))
			m_Command->ExecuteOnPress();
		else if (gamePadState.Gamepad.wButtons != DWORD(m_ControllerInput) && prevGamePadState.Gamepad.wButtons == DWORD(m_ControllerInput))
			m_Command->ExecuteOnRelease();
		else if (gamePadState.Gamepad.wButtons == DWORD(m_ControllerInput) && prevGamePadState.Gamepad.wButtons == DWORD(m_ControllerInput))
			m_Command->ExecuteOnHold({ 0,0 });
	}
	else if (gamePadConnected)
	{
		m_Command->ExecuteOnHold(GetAxis(gamePadState));
	}
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
