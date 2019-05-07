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
	std::map<int, InputAction*>::iterator itr = m_InputActions.begin();
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
			m_GamepadConnected[i] = false;
		}
		else
		{
			m_GamepadConnected[i] = true;
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

	std::map<int, InputAction*>::iterator it;

	for (it = m_InputActions.begin(); it != m_InputActions.end(); it++)
	{
		it->second->HandleInput(m_CurrentEvent, m_PreviousEvent, m_CurrentGpState[it->first], m_PreviousGpState[it->first], m_GamepadConnected[it->first]);
	}

	return true;
}

void dae::InputManager::SwapInputBuffer()
{
	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		m_PreviousGpState[i] = m_CurrentGpState[i];
	}
	m_PreviousEvent = m_CurrentEvent;
}

void dae::InputManager::AddInputAction(Command* command, SDL_Scancode keyBoardScanecode, ControllerInput controllerInput, int controllerId)
{
	InputAction* action = new InputAction(command, keyBoardScanecode, controllerInput);

	std::pair<std::map<int, InputAction*>::iterator, bool> returnValue;
	returnValue = m_InputActions.insert(std::pair<int, InputAction*>(controllerId, action));

	if (!returnValue.second) //was already in here log a warning
	{
		Logger::LogWarning(L"Input action: " + std::to_wstring(controllerId) + L" already defined!");
	}

}

void dae::InputManager::AddInputAction(Command* command, SDL_Scancode keyBoardScanecode)
{
	AddInputAction(command, keyBoardScanecode, ControllerInput::NONE, -1);;
}

void dae::InputManager::AddInputAction(Command* command, ControllerInput controllerInput, int controllerId)
{
	AddInputAction(command, SDL_SCANCODE_UNKNOWN, controllerInput, controllerId);;
}

//bool dae::InputManager::IsPressed(const std::wstring & inputActionName, unsigned int controllerId)
//{
//	if (m_InputActions.find(inputActionName) != m_InputActions.end())
//		return IsPressed(m_InputActions.find(inputActionName)->second, controllerId);
//	else
//		return false;
//}
//
//bool dae::InputManager::IsReleased(const std::wstring & inputActionName, unsigned int controllerId)
//{
//	if (m_InputActions.find(inputActionName) != m_InputActions.end())
//		return IsReleased(m_InputActions.find(inputActionName)->second, controllerId);
//	else
//		return false;
//}
//
//bool dae::InputManager::IsHolding(const std::wstring & inputActionName, unsigned int controllerId)
//{
//	if (m_InputActions.find(inputActionName) != m_InputActions.end())
//		return IsHolding(m_InputActions.find(inputActionName)->second, controllerId);
//	else
//		return false;
//}
//
//bool dae::InputManager::IsPressed(InputAction * inputActionPointer, unsigned int controllerId)
//{
//	return inputActionPointer->IsPressed(m_CurrentEvent, m_PreviousEvent, m_CurrentGpState[controllerId], m_PreviousGpState[controllerId]);
//}
//
//bool dae::InputManager::IsReleased(InputAction * inputActionPointer, unsigned int controllerId)
//{
//	return inputActionPointer->IsReleased(m_CurrentEvent, m_PreviousEvent, m_CurrentGpState[controllerId], m_PreviousGpState[controllerId]);
//}
//
//bool dae::InputManager::IsHolding(InputAction * inputActionPointer, unsigned int controllerId)
//{
//	return inputActionPointer->IsHolding(m_CurrentEvent, m_PreviousEvent, m_CurrentGpState[controllerId], m_PreviousGpState[controllerId]);
//}
//
//b2Vec2 dae::InputManager::GetControllerAxis(const std::wstring & inputActionName, unsigned int controllerId)
//{
//	return GetControllerAxis(m_InputActions.at(inputActionName), controllerId);
//}
//
//b2Vec2 dae::InputManager::GetControllerAxis(InputAction * inputActionPointer, unsigned int controllerId)
//{
//	if (m_CurrentGpConnected[controllerId])
//		return inputActionPointer->GetAxis(m_CurrentGpState[controllerId]);
//	return { 0,0 };
//}


