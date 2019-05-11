#pragma once
#include "BaseComponent.h"
#include <tuple>
#include <variant>
#include <functional>
#include "UserDefinedStates.h"

//Taken and modified from:
//https://sii.pl/blog/implementing-a-state-machine-in-c17/

namespace dae
{
	template <typename State>
	struct TransitionToState
	{
		template<typename StateMachine>
		void Execute(StateMachine& stateMachineRef)
		{
			stateMachineRef.template TransitionTo<State>();
		}
	};
	struct DoNothing
	{
		template<typename StateMachine>
		void Execute(StateMachine& stateMachineRef) {};
	};

	template<typename... States>
	class StateMachineComponent : public BaseComponent
	{
	public:
		StateMachineComponent() = default;
		~StateMachineComponent() = default;
		StateMachineComponent(const StateMachineComponent& other) = delete;
		StateMachineComponent(StateMachineComponent&& other) = delete;
		StateMachineComponent& operator=(const StateMachineComponent& other) = delete;
		StateMachineComponent& operator=(StateMachineComponent&& other) = delete;

		template <typename State>
		void TransitionTo()
		{
			m_CurrentState = &std::get<State>(m_States);
		}

		template <typename Event>
		void DoEvent(const Event& event)
		{
			auto passEventToState = [this, &event](auto statePtr) { statePtr->DoEvent(event).Execute(*this); };
			std::visit(passEventToState, m_CurrentState);
		}

	protected:
		virtual void Update() override { ; };
		virtual void Initialize() override { ; };
		virtual void Render() const override { ; };

	private:
		std::tuple<States...> m_States;
		std::variant<States*...> m_CurrentState{ &std::get<0>(m_States) };
	};
}

