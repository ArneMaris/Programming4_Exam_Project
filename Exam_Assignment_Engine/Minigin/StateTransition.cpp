#include "MiniginPCH.h"
#include "StateTransition.h"
#include "Response.h"
#include "StateMachineComponent.h"


dae::StateTransition::StateTransition(State * to, Response* response,bool onEnterPressed)
	:dae::StateTransition(nullptr, to, response, onEnterPressed)
{
}


dae::StateTransition::StateTransition(State * onlyFrom, State * to, Response* response, bool onEnterPressed)
	:m_OnEnter{onEnterPressed }
	,m_OnExit{!onEnterPressed }
	,m_pFromState{onlyFrom}
	,m_pToState{to}
	,m_ChangedThisFrame{ false }
{
	m_pResponses.push_back(response);
}

dae::StateTransition::StateTransition(State * to, const std::vector<Response*> responses, bool onEnterPressed)
	:dae::StateTransition(nullptr, to, responses, onEnterPressed)
{
}
dae::StateTransition::StateTransition(State * onlyFrom, State * to, const std::vector<Response*> responses, bool onEnterPressed)
	:m_OnEnter{ onEnterPressed }
	, m_OnExit{ !onEnterPressed }
	, m_pFromState{ onlyFrom }
	, m_pToState{ to }
	, m_ChangedThisFrame{false}
{
	m_pResponses.assign(responses.begin(), responses.end());
}


void dae::StateTransition::OnNotify(const NotifyEvent & notifyEvent, int notifierResponseId)
{
	//try to find notifier in the responseVector, if not present means this transition can't be calles by this notifier
	auto it = std::find_if(m_pResponses.begin(), m_pResponses.end(), [notifierResponseId](Response* resp) {return resp->GetResponseID() == notifierResponseId; });
	if (it == m_pResponses.end()) return;

	if (m_ChangedThisFrame)
	{
		m_ChangedThisFrame = false;
		return;
	}

	switch (notifyEvent)
	{
	case NotifyEvent::AnimationResponseTriggered:
		if (m_pFromState == nullptr)
			m_pStateMachine->SetToState(m_pToState);
		else
			m_pStateMachine->TryTransitionToState(m_pFromState, m_pToState);

		m_ChangedThisFrame = true;
		break;
	case NotifyEvent::InputPressed:
		m_pStateMachine->IncreasedPressCount();
	case NotifyEvent::CollisionStart:
		if (m_OnEnter)
		{
			if (m_pFromState == nullptr)
				m_pStateMachine->SetToState(m_pToState);
			else
			{
				if (m_pStateMachine->TryTransitionToState(m_pFromState, m_pToState))
					m_ChangedThisFrame = true;
			}

		}
		break;
	case NotifyEvent::InputReleased:
		m_pStateMachine->DecreasePressCount();
		if (m_pStateMachine->GetPressCount() != 0) return;
	case NotifyEvent::CollisionEnd:
		if (m_OnExit)
		{
			if (m_pFromState == nullptr)
				m_pStateMachine->SetToState(m_pToState);
			else
			{
				if (m_pStateMachine->TryTransitionToState(m_pFromState, m_pToState))
				{
					m_ChangedThisFrame = true;
					m_pStateMachine->GetGameObject()->GetComponent<TransformComponent>()->CancelMoveToPos();
				}
			}
		}
		break;
	}
}
