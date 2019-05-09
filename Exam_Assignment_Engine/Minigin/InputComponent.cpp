#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputManager.h"
#include "InputResponse.h"

dae::InputComponent::InputComponent(int controllerId, bool useKeyboardInput)
	:m_ControllerId{ controllerId }
	,m_UsingKeyboardInput {useKeyboardInput}
{
	InputManager::GetInstance().RegisterInputComponent(this);
}

dae::InputComponent::~InputComponent()
{
	for (auto& action : m_pInputActions)
	{
		delete action;
	}
	m_pInputActions.clear();
}

void dae::InputComponent::Update()
{

}

void dae::InputComponent::Initialize()
{

}

void dae::InputComponent::Render() const
{

}

void dae::InputComponent::HandleControllerInput(XINPUT_STATE& gamePadState, XINPUT_STATE& prevGamePadState)
{
	for (auto& action : m_pInputActions)
	{
		action->HandleControllerInput(gamePadState, prevGamePadState, m_ControllerId);
	}
}

void dae::InputComponent::HandleKeyboardInput(SDL_Event & e)
{
	for (auto& action : m_pInputActions)
	{
		action->HandleKeyBoardInput(e);
	}
}

void dae::InputComponent::AddInputAction(InputResponse* response, SDL_Keycode keyBoardScanecode, ControllerInput controllerInput)
{
	m_pInputActions.push_back(new InputAction(response, keyBoardScanecode, controllerInput));
}

void dae::InputComponent::AddInputAction(InputResponse* response, SDL_Keycode keyBoardScanecode)
{
	AddInputAction(response, keyBoardScanecode, ControllerInput::NONE);;
}

void dae::InputComponent::AddInputAction(InputResponse* response, ControllerInput controllerInput)
{
	AddInputAction(response, SDLK_UNKNOWN, controllerInput);;
}
