#pragma once
#include "State.h"

namespace PlayerFygarStates
{

	class PlayerFygarRun : public dae::State
	{
	public:
		PlayerFygarRun() = default;
		~PlayerFygarRun() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};

	class PlayerFygarGhost : public dae::State
	{
	public:
		PlayerFygarGhost() = default;
		~PlayerFygarGhost() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};

	class PlayerFygarAttacking : public dae::State
	{
	public:
		PlayerFygarAttacking() = default;
		~PlayerFygarAttacking() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};
}
