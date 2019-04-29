#include "MiniginPCH.h"
#include "InputManager.h"
#include "SDL_events.h"

dae::InputManager::InputManager()
{
	m_CurrentGpState = new XINPUT_STATE();
	m_PreviousGpState = new XINPUT_STATE();
	ZeroMemory(&m_PreviousGpState, sizeof(XINPUT_STATE));

	m_CurrentEvent = new SDL_Event;
}

void dae::InputManager::CleanUp()
{
	if (m_CurrentGpState)
		delete m_CurrentGpState;
	if (m_PreviousGpState)
		delete m_PreviousGpState;
	if (m_PreviousGpState)
		delete m_PreviousGpState;
	if (m_CurrentEvent)
		delete m_CurrentEvent;
	if (m_PreviousEvent)
		delete m_PreviousEvent;
}

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentGpState, sizeof(XINPUT_STATE));
	XInputGetState(0, m_CurrentGpState);
	while (SDL_PollEvent(m_CurrentEvent))
	{
		ImGui_ImplSDL2_ProcessEvent(m_CurrentEvent); //make sure ImGui also gets in the event
		switch (m_CurrentEvent->type)
		{
			case SDL_QUIT:
				return false;
				break;
		}
	}
	return true;
}



void dae::InputManager::SwapInputBuffer()
{
	m_PreviousEvent = m_CurrentEvent;
	m_PreviousGpState = m_PreviousGpState;
}

dae::InputAction* dae::InputManager::AddInputAction(const std::string& name, SDL_Scancode keyBoardScanecode, ControllerInput controllerInput)
{
	std::pair<std::unordered_map<const std::string, dae::InputAction*>::iterator, bool> returnValue;
	returnValue = m_InputActions.insert(std::pair<std::string, InputAction*>(name, new dae::InputAction(keyBoardScanecode, controllerInput)));

	if (!returnValue.second) //was already in here log a warning
	{
		Logger::LogWarning("Input action: " + name + " already defined!");
	}

	return returnValue.first->second;
}

bool dae::InputManager::IsPressed(const std::string & inputActionName)
{
	return IsPressed(m_InputActions.at(inputActionName));;
}

bool dae::InputManager::IsReleased(const std::string & inputActionName)
{
	return IsReleased(m_InputActions.at(inputActionName));;
}

bool dae::InputManager::IsHolding(const std::string & inputActionName)
{
	return IsHolding(m_InputActions.at(inputActionName));;
}

bool dae::InputManager::IsPressed(InputAction * inputActionPointer)
{
	return inputActionPointer->IsPressed(m_CurrentEvent, m_PreviousEvent, m_CurrentGpState, m_PreviousGpState);
}

bool dae::InputManager::IsReleased(InputAction * inputActionPointer)
{
	return inputActionPointer->IsReleased(m_CurrentEvent, m_PreviousEvent, m_CurrentGpState, m_PreviousGpState);
}

bool dae::InputManager::IsHolding(InputAction * inputActionPointer)
{

	return inputActionPointer->IsHolding(m_CurrentEvent, m_PreviousEvent, m_CurrentGpState, m_PreviousGpState);
}

b2Vec2 dae::InputManager::GetControllerAxis(const std::string & inputActionName)
{
	return GetControllerAxis(m_InputActions.at(inputActionName));
}

b2Vec2 dae::InputManager::GetControllerAxis(InputAction * inputActionPointer)
{
	return inputActionPointer->GetAxis(m_CurrentGpState);
}


//*****************************************************************************************
dae::InputAction::InputAction(SDL_Scancode scanCode = SDL_SCANCODE_UNKNOWN, ControllerInput controllerInput = ControllerInput::NONE)
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

bool dae::InputAction::IsPressed(SDL_Event* e, SDL_Event* ePrev, XINPUT_STATE* gamePadState, XINPUT_STATE* prevGamePadState)
{
	//KEYBOARD INPUT
	if (m_ScanCode != SDL_SCANCODE_UNKNOWN)
	{
		if (e->key.keysym.scancode == m_ScanCode && ePrev->key.keysym.scancode != m_ScanCode) // if now is true and prev is false key is just pressed
			return true;
	}

	//CONTROLLER INPUT
	if (!m_ControllerInputIsAxis)
	{
		if (gamePadState->Gamepad.wButtons == DWORD(m_ControllerInput) && prevGamePadState->Gamepad.wButtons != DWORD(m_ControllerInput))
			return true;
	}
	else
	{
		Logger::LogWarning("Trying to get Axis value from IsPressed(), this works only for buttons and will now returns false, use GetControllerAxis() instead!");
		return false;
	}
	return false;
}

bool dae::InputAction::IsReleased(SDL_Event* e, SDL_Event* ePrev, XINPUT_STATE* gamePadState, XINPUT_STATE* prevGamePadState)
{
	//KEYBOARD INPUT
	if (m_ScanCode != SDL_SCANCODE_UNKNOWN)
	{
		if (e->key.keysym.scancode != m_ScanCode && ePrev->key.keysym.scancode == m_ScanCode) // if now is false and prev is true key is just released
			return true;
	}

	//CONTROLLER INPUT
	if (!m_ControllerInputIsAxis)
	{
		if (gamePadState->Gamepad.wButtons != DWORD(m_ControllerInput) && prevGamePadState->Gamepad.wButtons == DWORD(m_ControllerInput))
			return true;
	}
	else
	{
		Logger::LogWarning("Trying to get Axis value from IsReleased(), this works only for buttons and will now returns false, use GetControllerAxis() instead!");
		return false;
	}
	return false;
}

bool dae::InputAction::IsHolding(SDL_Event* e, SDL_Event* ePrev, XINPUT_STATE* gamePadState, XINPUT_STATE* prevGamePadState)
{
	//KEYBOARD INPUT
	if (m_ScanCode != SDL_SCANCODE_UNKNOWN)
	{
		if (e->key.keysym.scancode == m_ScanCode && ePrev->key.keysym.scancode == m_ScanCode) //if both prev and now is true means button is being held
			return true;
	}

	//CONTROLLER INPUT
	if (!m_ControllerInputIsAxis)
	{
		if (gamePadState->Gamepad.wButtons == DWORD(m_ControllerInput) && prevGamePadState->Gamepad.wButtons == DWORD(m_ControllerInput))
			return true;
	}
	else
	{
		Logger::LogWarning("Trying to get Axis value from IsHolding(), this works only for buttons and will now returns false, use GetControllerAxis() instead!");
		return false;
	}

	return false;
}

b2Vec2 dae::InputAction::GetAxis(XINPUT_STATE * gamePadState)
{
	b2Vec2 stickInput{0,0}; 
	switch (m_ControllerInput)
	{
	case ControllerInput::JoyStickLeft:
		stickInput = { gamePadState->Gamepad.sThumbLX, gamePadState->Gamepad.sThumbLY };
		ClampStickInput(stickInput, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	case ControllerInput::JoyStickRight:
		stickInput = { gamePadState->Gamepad.sThumbRX, gamePadState->Gamepad.sThumbRY };
		ClampStickInput(stickInput, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		break;
	case ControllerInput::TriggerLeft:
		stickInput = { (int(gamePadState->Gamepad.bLeftTrigger) / 255), 0 };
		break;
	case ControllerInput::TriggerRight:
		stickInput = { (int(gamePadState->Gamepad.bRightTrigger) / 255), 0 };
		break;
	default:
		Logger::LogWarning("Trying to do GetAxis() on a button, this only works on JoySticks and Triggers, will now return {0,0}");
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
	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		normalizedMagnitude = 0.0;
	}
	stickInput = { normalizedMagnitude * normalizedLX, normalizedMagnitude * normalizedLY };
}

bool dae::InputAction::GetGamePadButtonDown(XINPUT_STATE gamePadState)
{
	

	return false;
}
