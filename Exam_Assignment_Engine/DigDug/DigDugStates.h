#pragma once
#include "State.h"

namespace DigDugStates
{

	class Idle : public dae::State
	{
	public:
		Idle() = default;
		~Idle() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};

	class Run : public dae::State
	{
	public:
		Run() = default;
		~Run() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};

	class Dead : public dae::State
	{
	public:
		Dead() = default;
		~Dead() = default;

		virtual void OnStateEnter() override;
		virtual void OnStateExit() override;
		virtual void InState() override;
	};
}