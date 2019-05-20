#pragma once

namespace dae
{
	class GameObject;
	class State
	{
	public:
		explicit State() = default;
		virtual ~State() = default;

		State(const State& other) = delete;
		State(State&& other) = delete;
		State& operator=(const State& other) = delete;
		State& operator=(State&& other) = delete;

		//Called the frame the statemachine enters this state
		virtual void OnStateEnter() = 0;

		//Called the frame the statemachine exits this state
		virtual void OnStateExit() = 0;

		//Called every frame the statemachine is in this state
		virtual void InState() = 0;

		void SetOwnerObject(GameObject* newOwner) { m_pOwnerObject = newOwner; };

	protected:
		GameObject* m_pOwnerObject = nullptr;
	};

}
