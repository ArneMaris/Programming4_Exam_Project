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
	while (SDL_PollEvent(&m_CurrentEvent))
	{
		ImGui_ImplSDL2_ProcessEvent(&m_CurrentEvent); //make sure ImGui also gets in the event
		switch (m_CurrentEvent.type)
		{
		case SDL_QUIT:
		case SDL_WINDOWEVENT_CLOSE:
			return false;
			break;
		}
		for (auto action : m_InputActions)
		{
			action.second->HandleKeyBoardInput(m_CurrentEvent);
		}
	}
	for (auto action : m_InputActions)
	{
		action.second->HandleControllerInput(m_CurrentGpState[action.first], m_PreviousGpState[action.first], m_GamepadConnected[action.first]);
	}
	return true;
}

void dae::InputManager::SwapInputBuffer()
{
	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		m_PreviousGpState[i] = m_CurrentGpState[i];
	}
}

void dae::InputManager::AddInputAction(Command* command, SDL_Keycode keyBoardScanecode, ControllerInput controllerInput, int controllerId)
{
	m_InputActions.insert(std::pair<int, InputAction*>(controllerId, new InputAction(command, keyBoardScanecode, controllerInput)));
}

void dae::InputManager::AddInputAction(Command* command, SDL_Keycode keyBoardScanecode)
{
	AddInputAction(command, keyBoardScanecode, ControllerInput::NONE, -1);;
}

void dae::InputManager::AddInputAction(Command* command, ControllerInput controllerInput, int controllerId)
{
	AddInputAction(command, SDLK_UNKNOWN, controllerInput, controllerId);;
}


