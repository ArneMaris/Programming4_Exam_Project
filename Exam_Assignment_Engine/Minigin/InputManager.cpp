#include "MiniginPCH.h"
#include "InputManager.h"
#include "SDL_events.h"
#include "InputAction.h"
#include "InputComponent.h"

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
	m_pInputComponents.clear();
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event ev;
	SDL_PollEvent(&ev);
	if (ev.type == SDL_QUIT) return true;
	ImGui_ImplSDL2_ProcessEvent(&ev); //make sure ImGui also gets in the event

	//get the keyboardState and send it to all inputComponents to handle
	m_KeyBoardState = SDL_GetKeyboardState(NULL);
	for (auto& inputComp : m_pInputComponents)
	{
		inputComp->HandleKeyboardInput(m_KeyBoardState, &m_PrevKeyBoardState);
	}

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
	for (auto& inputComp : m_pInputComponents)
	{
		int id = inputComp->m_ControllerId;
		if (id >= 0 && id < MAX_CONTROLLERS)
			if (m_GamepadConnected[id])
				inputComp->HandleControllerInput(m_CurrentGpState[id], m_PreviousGpState[id]);
	}
	return false;
}

void dae::InputManager::SwapInputBuffer()
{
	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		m_PreviousGpState[i] = m_CurrentGpState[i];
	}
	m_PrevKeyBoardState = *m_KeyBoardState;
}

void dae::InputManager::RegisterInputComponent(InputComponent * inputComp)
{
	m_pInputComponents.push_back(inputComp);
}

void dae::InputManager::UnregisterInputComponent(InputComponent * inputComp)
{
	m_pInputComponents.erase(std::remove(m_pInputComponents.begin(), m_pInputComponents.end(), inputComp), m_pInputComponents.end());
}

int dae::InputManager::GetAmountOfConnectedControllers()
{
	int count = 0;
	for (int i = 0; i < MAX_CONTROLLERS; i++)
		if (m_GamepadConnected[i])
			++count;

	return count;
}


