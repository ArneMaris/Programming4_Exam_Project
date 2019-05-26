#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputManager.h"
#include "InputResponse.h"
#include "StateMachineComponent.h"

dae::InputComponent::InputComponent(int controllerId, bool useKeyboardInput)
	:m_ControllerId{ controllerId }
	,m_UsingKeyboardInput {useKeyboardInput}
	,m_Enabled{true}
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
	InputManager::GetInstance().UnregisterInputComponent(this);
}

void dae::InputComponent::Update()
{

}

void dae::InputComponent::Initialize()
{
	m_pScene = SceneManager::GetInstance().GetActiveScene();

	if (m_pGameObject->GetComponent<StateMachineComponent>() != nullptr)
	{
		for (auto& trans : m_pGameObject->GetComponent<StateMachineComponent>()->GetStateTransitions())
		{
			for (auto& inputAct : m_pInputActions)
			{
				inputAct->GetResponse()->AddObserver(std::reinterpret_pointer_cast<Observer>(trans));
			}
		}
	}
}

void dae::InputComponent::Render() const
{

}

void dae::InputComponent::HandleControllerInput(XINPUT_STATE& gamePadState, XINPUT_STATE& prevGamePadState)
{
	if (m_Enabled && SceneManager::GetInstance().GetActiveScene() == m_pScene)
	{
		for (auto& action : m_pInputActions)
		{
			action->HandleControllerInput(gamePadState, prevGamePadState);
		}
	}
}

void dae::InputComponent::HandleKeyboardInput(const UINT8* keyboardState, const UINT8* prevKeyboardState)
{
	if (m_Enabled && SceneManager::GetInstance().GetActiveScene() == m_pScene)
	{
		if (m_UsingKeyboardInput)
		{
			for (auto& action : m_pInputActions)
			{
				action->HandleKeyBoardInput(keyboardState, prevKeyboardState);
			}
		}
	}
}

void dae::InputComponent::AddInputAction(InputResponse* response, SDL_Keycode keyBoardScanecode, ControllerInput controllerInput)
{
	m_pInputActions.push_back(new InputAction(response, keyBoardScanecode, controllerInput));
	response->SetOwnerObject(m_pGameObject);
}

void dae::InputComponent::AddInputAction(InputResponse* response, SDL_Keycode keyBoardScanecode)
{
	AddInputAction(response, keyBoardScanecode, ControllerInput::NONE);;
}

void dae::InputComponent::AddInputAction(InputResponse* response, ControllerInput controllerInput)
{
	AddInputAction(response, SDLK_UNKNOWN, controllerInput);;
}

void dae::InputComponent::GetInputAction(const std::wstring & responseName)
{
	UNREFERENCED_PARAMETER(responseName);
}
