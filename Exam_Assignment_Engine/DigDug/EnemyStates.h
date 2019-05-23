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

	private:
		float m_PrevXPos = -999;
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
	private:
		float m_DeflateTimer = 0;
	};

	class BlowUpTwo : public dae::State
	{
	public:
		BlowUpTwo() = default;
		~BlowUpTwo() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	private:
		float m_DeflateTimer = 0;
	};

	class BlowUpThree : public dae::State
	{
	public:
		BlowUpThree() = default;
		~BlowUpThree() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;

	private:
		float m_DeflateTimer = 0;
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

	class Attacking : public dae::State
	{
	public:
		Attacking() = default;
		~Attacking() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};

	class Dragged : public dae::State
	{
	public:
		Dragged() = default;
		~Dragged() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	private:
		float m_Height;
	};
	class Squashed : public dae::State
	{
	public:
		Squashed() = default;
		~Squashed() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	private:
		float m_Timer;
	};
}
