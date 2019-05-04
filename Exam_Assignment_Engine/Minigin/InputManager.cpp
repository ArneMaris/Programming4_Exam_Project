#include "MiniginPCH.h"
#include "InputManager.h"
#include "SDL_events.h"
#include "InputAction.h"

using namespace dae;

dae::InputManager::InputManager()
{
	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		ZeroMemory(&m_CurrentGpState[i], sizeof(XINPUT_STATE));
		ZeroMemory(&m_PreviousGpState[i], sizeof(XINPUT_STATE));
	}
}

void dae::InputManager::CleanUp()
{
	std::map<std::wstring, InputAction*>::iterator itr = m_InputActions.begin();
	if (itr != m_InputActions.end())
	{
		delete itr->second;
		m_InputActions.erase(itr);
	}
}

bool dae::InputManager::ProcessInput()
{
	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		DWORD result = XInputGetState(i, &m_CurrentGpState[i]);
		if (result != ERROR_SUCCESS) // if not succes means controller not connected zero out memory to make sure you have no trash there
		{
			ZeroMemory(&m_CurrentGpState[i], sizeof(XINPUT_STATE));
			m_CurrentGpConnected[i] = false;
		}
		else
		{
			m_CurrentGpConnected[i] = true;
		}
	}
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
		m_CurrentEvent = ev;
	return true;
}

void dae::InputManager::SwapInputBuffer()
{
	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		m_PreviousGpState[i] = m_CurrentGpState[i];
		m_PreviousGpConnected[i] = m_CurrentGpConnected[i];
	}
	m_PreviousEvent = m_CurrentEvent;
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

bool dae::InputManager::IsPressed(const std::wstring & inputActionName, unsigned int controllerId)
{
	if (m_InputActions.find(inputActionName) != m_InputActions.end())
		return IsPressed(m_InputActions.find(inputActionName)->second, controllerId);
	else
		return false;
}

bool dae::InputManager::IsReleased(const std::wstring & inputActionName, unsigned int controllerId)
{
	if (m_InputActions.find(inputActionName) != m_InputActions.end())
		return IsReleased(m_InputActions.find(inputActionName)->second, controllerId);
	else
		return false;
}

bool dae::InputManager::IsHolding(const std::wstring & inputActionName, unsigned int controllerId)
{
	if (m_InputActions.find(inputActionName) != m_InputActions.end())
		return IsHolding(m_InputActions.find(inputActionName)->second, controllerId);
	else
		return false;
}

bool dae::InputManager::IsPressed(InputAction * inputActionPointer, unsigned int controllerId)
{
	if (m_CurrentGpConnected[controllerId] && m_PreviousGpConnected[controllerId])
		return inputActionPointer->IsPressed(m_CurrentEvent, m_PreviousEvent, m_CurrentGpState[controllerId], m_PreviousGpState[controllerId]);
	return false;
}

bool dae::InputManager::IsReleased(InputAction * inputActionPointer, unsigned int controllerId)
{
	if (m_CurrentGpConnected[controllerId] && m_PreviousGpConnected[controllerId])
		return inputActionPointer->IsReleased(m_CurrentEvent, m_PreviousEvent, m_CurrentGpState[controllerId], m_PreviousGpState[controllerId]);
	return false;
}

bool dae::InputManager::IsHolding(InputAction * inputActionPointer, unsigned int controllerId)
{
	if (m_CurrentGpConnected[controllerId] && m_PreviousGpConnected[controllerId])
		return inputActionPointer->IsHolding(m_CurrentEvent, m_PreviousEvent, m_CurrentGpState[controllerId], m_PreviousGpState[controllerId]);
	return false;
}

b2Vec2 dae::InputManager::GetControllerAxis(const std::wstring & inputActionName, unsigned int controllerId)
{
	return GetControllerAxis(m_InputActions.at(inputActionName), controllerId);
}

b2Vec2 dae::InputManager::GetControllerAxis(InputAction * inputActionPointer, unsigned int controllerId)
{
	if (m_CurrentGpConnected[controllerId])
		return inputActionPointer->GetAxis(m_CurrentGpState[controllerId]);
	return { 0,0 };
}


