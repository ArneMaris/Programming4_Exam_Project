#pragma once
#include "AnimatedSpriteComponent.h"
#include "Observer.h"


namespace dae
{
	class State;
	class Response;
	class StateMachineComponent;

	//use this class to make automatic state transitions based on a Collision-, Input- or Anim-Response
	class StateTransition : public Observer
	{
		friend class StateMachineComponent;
	public:
		StateTransition(State* onlyFrom, State* to, Response* response, bool onEnterPressed);
		StateTransition(State* to, Response* response,  bool onEnterPressed);
		StateTransition(State* onlyFrom, State* to, const std::vector<Response*> responses, bool onEnterPressed);
		StateTransition(State* to, const std::vector<Response*> responses, bool onEnterPressed);
		~StateTransition() = default;

		virtual void OnNotify(const NotifyEvent& notifyEvent, int notifierResponseId) override;

	private:
		std::vector<Response*> m_pResponses;

		bool m_OnEnter;
		bool m_OnExit;

		State* m_pFromState;
		State* m_pToState;

		StateMachineComponent* m_pStateMachine;
	};
}

