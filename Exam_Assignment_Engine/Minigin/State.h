#pragma once

namespace dae
{
	class State
	{
	public:
		State() = default;
		virtual ~State() = default;

		//Called the frame the statemachine enters this state
		virtual void OnStateEnter() = 0;

		//Called the frame the statemachine exits this state
		virtual void OnStateExit() = 0;

		//Called every frame the statemachine is in this state
		virtual void WhenInState() = 0;
	};

}
