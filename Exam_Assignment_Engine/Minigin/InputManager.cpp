#include "MiniginPCH.h"
#include "InputManager.h"
#include "SDL_events.h"
#include "InputAction.h"

using namespace dae;

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
	XInputGetState(0, m_CurrentGpState);
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		ImGui_ImplSDL2_ProcessEvent(&ev); //make sure ImGui also gets in the event
		switch (ev.type)
		{
		case SDL_QUIT:
			return false;
			break;
		}
	}
	if (ev.type != SDL_QUIT && ev.type != SDL_WINDOWEVENT_CLOSE)
		m_CurrentEvent = &ev;
	return true;
}

void dae::InputManager::SwapInputBuffer()
{
	m_PreviousEvent = m_CurrentEvent;
	m_PreviousGpState = m_PreviousGpState;
	ZeroMemory(&m_CurrentGpState, sizeof(XINPUT_STATE));
}

InputAction* dae::InputManager::AddInputAction(const std::wstring& name, SDL_Scancode keyBoardScanecode, ControllerInput controllerInput)
{
	InputAction* action = new InputAction(keyBoardScanecode, controllerInput);
	if (action == nullptr)
		return nullptr;

	std::pair<std::map<const std::wstring, InputAction*>::iterator, bool> returnValue;
	returnValue = m_InputActions.insert(std::pair<const std::wstring, InputAction*>(name, action));

	if (!returnValue.second) //was already in here log a warning
	{
		Logger::LogWarning(L"Input action: " + name + L" already defined!");
	}

	return returnValue.first->second;
}

InputAction* dae::InputManager::AddInputAction(const std::wstring & name)
{
	return AddInputAction(name, SDL_SCANCODE_UNKNOWN, ControllerInput::NONE);
}

InputAction* dae::InputManager::AddInputAction(const std::wstring & name, SDL_Scancode keyBoardScanecode)
{
	return AddInputAction(name, keyBoardScanecode, ControllerInput::NONE);;
}

InputAction* dae::InputManager::AddInputAction(const std::wstring & name, ControllerInput controllerInput)
{
	return AddInputAction(name, SDL_SCANCODE_UNKNOWN, controllerInput);;
}

bool dae::InputManager::IsPressed(const std::wstring & inputActionName)
{
	return IsPressed(m_InputActions.at(inputActionName));;
}

bool dae::InputManager::IsReleased(const std::wstring & inputActionName)
{
	return IsReleased(m_InputActions.at(inputActionName));;
}

bool dae::InputManager::IsHolding(const std::wstring & inputActionName)
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

b2Vec2 dae::InputManager::GetControllerAxis(const std::wstring & inputActionName)
{
	return GetControllerAxis(m_InputActions.at(inputActionName));
}

b2Vec2 dae::InputManager::GetControllerAxis(InputAction * inputActionPointer)
{
	return inputActionPointer->GetAxis(m_CurrentGpState);
}


