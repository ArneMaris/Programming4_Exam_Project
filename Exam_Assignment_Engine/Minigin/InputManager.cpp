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
		for (auto& inputComp : m_pInputComponents)
		{
			inputComp->HandleKeyboardInput(m_CurrentEvent);
		}
	}
	for (auto& inputComp : m_pInputComponents)
	{
		int id = inputComp->m_ControllerId;
		if (m_GamepadConnected[id])
			inputComp->HandleControllerInput(m_CurrentGpState[id], m_PreviousGpState[id]);
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

void dae::InputManager::RegisterInputComponent(InputComponent * inputComp)
{
	m_pInputComponents.push_back(inputComp);
}


