#pragma once
#include "State.h"

namespace EnemyStates
{
	class Run : public dae::State
	{
	public:
		Run() = default;
		~Run() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};

	class Ghost : public dae::State
	{
	public:
		Ghost() = default;
		~Ghost() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};

	class BlowUpOne : public dae::State
	{
	public:
		BlowUpOne() = default;
		~BlowUpOne() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};

	class BlowUpTwo : public dae::State
	{
	public:
		BlowUpTwo() = default;
		~BlowUpTwo() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};

	class BlowUpThree : public dae::State
	{
	public:
		BlowUpThree() = default;
		~BlowUpThree() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};

	class Pop : public dae::State
	{
	public:
		Pop() = default;
		~Pop() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};
}
