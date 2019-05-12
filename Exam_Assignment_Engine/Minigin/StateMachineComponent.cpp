#include "MiniginPCH.h"
#include "StateMachineComponent.h"
#include "State.h"
#include "StateTransition.h"

dae::StateMachineComponent::~StateMachineComponent()
{
	for (auto it = m_pStates.begin(); it != m_pStates.end(); ++it)
	{
		delete it->second;
	}
	m_pStates.clear();
	for (auto it = m_pStateTransitions.begin(); it != m_pStateTransitions.end(); ++it)
	{
		delete (*it);
	}
	m_pStateTransitions.clear();
	m_pCurrentState = nullptr;
}

void dae::StateMachineComponent::AddState(const std::wstring& name, State* state, bool defaultState)
{
	m_pStates.insert(std::make_pair(std::move(name),state));
	if (defaultState)
		m_DefaultStateName = name;
}

void dae::StateMachineComponent::AddStateToStateTransition(const std::wstring& fromName, const std::wstring& toName, Response* response, bool onEnterPressed)
{
	if (m_pStates.find(fromName) != m_pStates.end() && m_pStates.find(toName) != m_pStates.end())
	{
		m_pStateTransitions.push_back(new StateTransition(m_pStates.at(fromName), m_pStates.at(toName), response, onEnterPressed));
		m_pStateTransitions.back()->m_pStateMachine = this;
	}
	else if (m_pStates.find(toName) != m_pStates.end())
	{
		m_pStateTransitions.push_back(new StateTransition(nullptr, m_pStates.at(toName), response, onEnterPressed));
		m_pStateTransitions.back()->m_pStateMachine = this;
	}
}

void dae::StateMachineComponent::AddToStateTransition(const std::wstring & toName, Response * response, bool onEnterPressed)
{
	if (m_pStates.find(toName) != m_pStates.end())
	{
		m_pStateTransitions.push_back(new StateTransition(nullptr, m_pStates.at(toName), response, onEnterPressed));
		m_pStateTransitions.back()->m_pStateMachine = this;
	}
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
	if (m_pCurrentState != nullptr)
		m_pCurrentState->InState();
}

void dae::StateMachineComponent::Initialize()
{
	if (m_pStates.size() <= 0)
	{
		Logger::GetInstance().LogWarning(L"Useless StateMachineComponent, No states!");
	}
	else
	{
		auto it = m_pStates.find(m_DefaultStateName);
		if (it != m_pStates.end())
		{
			m_pCurrentState = it->second;
		}
		else
		{
			Logger::GetInstance().LogWarning(L"No default state in StateMachineComponent, using alphabetically first one!");
			m_pCurrentState = m_pStates.begin()->second;
		}
	}
}

void dae::StateMachineComponent::Render() const
{
}
