#pragma once
#include "BaseComponent.h"
#include <map>

namespace dae
{
	class State;
	class StateTransition;
	class Response;

	class StateMachineComponent : public BaseComponent
	{
	public:
		StateMachineComponent() = default;
		~StateMachineComponent();
		StateMachineComponent(const StateMachineComponent& other) = delete;
		StateMachineComponent(StateMachineComponent&& other) = delete;
		StateMachineComponent& operator=(const StateMachineComponent& other) = delete;
		StateMachineComponent& operator=(StateMachineComponent&& other) = delete;

		void AddState(const std::wstring& name, State* state, bool defaultState);
		void AddStateToStateTransition(const std::wstring& fromName, const std::wstring& toName, Response* response, bool onEnterPressed);
		void AddToStateTransition( const std::wstring& toName, Response* response, bool onEnterPressed);

		void SetToState(State* state);
		void TryTransitionToState(State* fromState, State* toState);

		std::vector<std::shared_ptr<StateTransition>> GetStateTransitions() const {return m_pStateTransitions;};
	
	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;

	private:
		std::map<const std::wstring, State*> m_pStates;
		//std::vector<State*> m_pStates;
		std::vector<std::shared_ptr<StateTransition>> m_pStateTransitions;

		State* m_pCurrentState = nullptr;

		std::wstring m_DefaultStateName =L"";
	};
}

