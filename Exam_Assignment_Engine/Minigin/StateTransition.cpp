#include "MiniginPCH.h"
#include "StateTransition.h"
#include "Response.h"
#include "StateMachineComponent.h"


dae::StateTransition::StateTransition(State * to, Response* response,bool onEnterPressed)
	:dae::StateTransition(nullptr, to, response, onEnterPressed)
{}

dae::StateTransition::StateTransition(State * onlyFrom, State * to, Response* response, bool onEnterPressed)
	:m_pResponse{response}
	,m_OnEnter{onEnterPressed }
	,m_OnExit{!onEnterPressed }
	,m_pFromState{onlyFrom}
	,m_pToState{to}
{
}

void dae::StateTransition::OnNotify(const NotifyEvent & notifyEvent, Response* notifier)
{
	if (typeid(*m_pResponse) != typeid(*notifier)) return;

	switch (notifyEvent)
	{
	case NotifyEvent::AnimationResponseTriggered:
		if (m_pFromState == nullptr)
			m_pStateMachine->SetToState(m_pToState);
		else
			m_pStateMachine->TryTransitionToState(m_pFromState, m_pToState);
		break;
	case NotifyEvent::InputPressed:
	case NotifyEvent::CollisionStart:
		if (m_OnEnter)
		{
			if (m_pFromState == nullptr)
				m_pStateMachine->SetToState(m_pToState);
			else
				m_pStateMachine->TryTransitionToState(m_pFromState, m_pToState);
		}
		break;
	case NotifyEvent::InputReleased:
	case NotifyEvent::CollisionEnd:
		if (m_OnExit)
		{
			if (m_pFromState == nullptr)
				m_pStateMachine->SetToState(m_pToState);
			else
				m_pStateMachine->TryTransitionToState(m_pFromState, m_pToState);
		}
		break;
	}
}
