#pragma once
#include "AnimatedSpriteComponent.h"
#include "Observer.h"


namespace dae
{
	class State;
	class Response;
	class StateMachineComponent;

	class StateTransition : public Observer
	{
		friend class StateMachineComponent;
	public:
		StateTransition(State* onlyFrom, State* to, Response* response, bool onEnter, bool onExit);
		StateTransition(State* to, Response* response, bool onEnter, bool onExit);
		~StateTransition() = default;

		virtual void OnNotify(const NotifyEvent& notifyEvent, Response* notifier) override;

	private:
		Response* m_pResponse;

		bool m_OnEnter;
		bool m_OnExit;

		State* m_pFromState;
		State* m_pToState;

		StateMachineComponent* m_pStateMachine;
	};
}

