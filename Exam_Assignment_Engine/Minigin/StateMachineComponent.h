#pragma once
#include "BaseComponent.h"
namespace dae
{
	class State;
	class StateTransition;
	class StateMachineComponent : public BaseComponent
	{
	public:
		StateMachineComponent() = default;
		~StateMachineComponent();
		StateMachineComponent(const StateMachineComponent& other) = delete;
		StateMachineComponent(StateMachineComponent&& other) = delete;
		StateMachineComponent& operator=(const StateMachineComponent& other) = delete;
		StateMachineComponent& operator=(StateMachineComponent&& other) = delete;

		void AddState(State* state);
		void AddStateTransition(StateTransition* transition);

		void RemoveState(State* state);
		void RemoveStateTransition(StateTransition* transition);

		void SetToState(State* state);
		void TryTransitionToState(State* fromState, State* toState);

		std::vector<StateTransition*> GetStateTransitions() const {return m_pStateTransitions;};
	

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;

	private:
		std::vector<State*> m_pStates;
		std::vector<StateTransition*> m_pStateTransitions;

		State* m_pCurrentState = nullptr;
	};
}

