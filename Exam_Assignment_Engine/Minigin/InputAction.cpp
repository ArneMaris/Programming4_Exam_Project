#include "MiniginPCH.h"
#include "InputAction.h"
#include "SDL_events.h"
#include "InputResponse.h"

dae::InputAction::InputAction(InputResponse* response, SDL_Keycode keyCode, ControllerInput controllerInput)
	:m_ControllerInputIsAxis{false}
	, m_pResponse{ response }
	, m_KeyHeld{false}
{
	m_Scancode = SDL_GetScancodeFromKey(keyCode);
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

dae::InputAction::~InputAction()
{
	delete m_pResponse;
}

void dae::InputAction::HandleKeyBoardInput(const UINT8* keyBoardState, const UINT8* prevKeyboardState)
{
	//KEYBOARD INPUT
	UNREFERENCED_PARAMETER(prevKeyboardState);
	if (m_Scancode != SDL_SCANCODE_UNKNOWN)
	{
		if (keyBoardState[m_Scancode] == 1 && m_KeyHeld)
		{
			m_pResponse->ExecuteOnHold({ 0,0 });
		}
		if (keyBoardState[m_Scancode] == 0 && m_KeyHeld)
		{
			m_pResponse->ExecuteOnRelease();
			m_pResponse->Notify(NotifyEvent::InputReleased);
			m_KeyHeld = false;
		}
		else if (keyBoardState[m_Scancode] == 1 && !m_KeyHeld) // if now is true and prev is false key is just pressed
		{
			m_pResponse->ExecuteOnPress();
			m_pResponse->Notify(NotifyEvent::InputPressed);
			m_KeyHeld = true;
		}
	}
}


void dae::InputAction::HandleControllerInput(XINPUT_STATE& gamePadState, XINPUT_STATE& prevGamePadState)
{
	if (!m_ControllerInputIsAxis && m_ControllerInput != ControllerInput::NONE)
	{
		if (gamePadState.Gamepad.wButtons == DWORD(m_ControllerInput) && prevGamePadState.Gamepad.wButtons != DWORD(m_ControllerInput))
		{
			m_pResponse->ExecuteOnPress();
			m_pResponse->Notify(NotifyEvent::InputPressed);
		}
		else if (gamePadState.Gamepad.wButtons != DWORD(m_ControllerInput) && prevGamePadState.Gamepad.wButtons == DWORD(m_ControllerInput))
		{
			m_pResponse->ExecuteOnRelease();
			m_pResponse->Notify(NotifyEvent::InputReleased);
		}
		else if (gamePadState.Gamepad.wButtons == DWORD(m_ControllerInput) && prevGamePadState.Gamepad.wButtons == DWORD(m_ControllerInput))
		{
			m_pResponse->ExecuteOnHold({ 0,0 });
		}
	}
	else if (m_ControllerInput != ControllerInput::NONE)
	{
		b2Vec2 prevAxis = GetAxis(prevGamePadState);
		if (!prevAxis.IsValid()) return;

		b2Vec2 axis = GetAxis(gamePadState);

		if (prevAxis.Length() < float32(0.1f) && axis.Length() >= float32(0.1f))
		{
			m_pResponse->ExecuteOnPress();
			m_pResponse->Notify(NotifyEvent::InputPressed);
		}
		else if (axis.Length() < float32(0.1f) && prevAxis.Length() >= float32(0.1f))
		{
			m_pResponse->ExecuteOnRelease();
			m_pResponse->Notify(NotifyEvent::InputReleased);
		}
		else if (axis.Length() >= float32(0.1f) && prevAxis.Length() >= float32(0.1f))
		{
			m_pResponse->ExecuteOnHold(axis);
		}
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
		break;
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
