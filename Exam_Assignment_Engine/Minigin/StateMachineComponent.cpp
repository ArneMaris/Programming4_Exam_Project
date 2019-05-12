#include "MiniginPCH.h"
#include "StateMachineComponent.h"
#include "State.h"
#include "StateTransition.h"


dae::StateMachineComponent::~StateMachineComponent()
{
	for (auto it = m_pStates.begin(); it != m_pStates.end(); ++it)
	{
		delete (*it);
	}
	m_pStates.clear();
	for (auto it = m_pStateTransitions.begin(); it != m_pStateTransitions.end(); ++it)
	{
		delete (*it);
	}
	m_pStateTransitions.clear();
	m_pCurrentState = nullptr;
}

void dae::StateMachineComponent::AddState(State * state)
{
	if (std::find_if(m_pStates.begin(), m_pStates.end(),
		[state](State* st) {return typeid(*state) == typeid(*st); }) == m_pStates.end())
	{
		m_pStates.push_back(state);
	}
	else
	{
		Logger::GetInstance().LogWarning(L"Trying to add the same state twice, call ignored!");
	}
}

void dae::StateMachineComponent::AddStateTransition(StateTransition * transition)
{
	m_pStateTransitions.push_back(transition);
	transition->m_pStateMachine = this;
}

void dae::StateMachineComponent::RemoveState(State * state)
{
	for (auto& pointer : m_pStates)
	{
		if (pointer == state)
		{
			delete pointer;
			pointer = nullptr;
			break;
		}
	}
	m_pStates.erase(std::remove(m_pStates.begin(), m_pStates.end(), nullptr), m_pStates.end());
}

void dae::StateMachineComponent::RemoveStateTransition(StateTransition * transition)
{
	for (auto& pointer : m_pStateTransitions)
	{
		if (pointer == transition)
		{
			delete pointer;
			pointer = nullptr;
			break;
		}
	}
	m_pStateTransitions.erase(std::remove(m_pStateTransitions.begin(), m_pStateTransitions.end(), nullptr), m_pStateTransitions.end());
}

void dae::StateMachineComponent::SetToState(State* state)
{
	m_pCurrentState->OnStateExit();
	m_pCurrentState = state;
	m_pCurrentState->OnStateEnter();
}

void dae::StateMachineComponent::TryTransitionToState(State * fromState, State * toState)
{
	if (typeid(*m_pCurrentState) == typeid(*fromState)) //only do it when currently in the fromState
	{
		m_pCurrentState->OnStateExit();
		m_pCurrentState = toState;
		m_pCurrentState->OnStateEnter();
	}
}

void dae::StateMachineComponent::Update()
{
	m_pCurrentState->WhenInState();
}

void dae::StateMachineComponent::Initialize()
{
}

void dae::StateMachineComponent::Render() const
{
}
