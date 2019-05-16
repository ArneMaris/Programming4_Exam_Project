#include "pch.h"
#include "States.h"

void StateIdle::OnStateEnter()
{
	dae::Logger::GetInstance().LogInfo(L"Entered IdleState");
}

void StateIdle::OnStateExit()
{
	dae::Logger::GetInstance().LogInfo(L"Left IdleState");
}

void StateIdle::InState()
{

}


void StateRunning::OnStateEnter()
{
	dae::Logger::GetInstance().LogInfo(L"Entered RunState");
}

void StateRunning::OnStateExit()
{
	dae::Logger::GetInstance().LogInfo(L"Left RunState");
}

void StateRunning::InState()
{
}


void StateDead::OnStateEnter()
{
	dae::Logger::GetInstance().LogInfo(L"Entered DeadState");
}

void StateDead::OnStateExit()
{
}

void StateDead::InState()
{
}
