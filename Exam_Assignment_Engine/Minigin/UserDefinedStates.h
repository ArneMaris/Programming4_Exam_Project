#pragma once
#include "GameObject.h"

//How to use StateMachineComponent?
//1) Add your states and stateTranstitions here (or in another file)
//2) Add your events that cause these stateTransitions (same file)
//3) Add a new StateMachineComponent to a GameObject, type it with all the states you want it to use (yes you can re-use states on multiple StateMachineComponents!)
	//m_GameObject->AddComponent(new StateMachineComponent<State1, State2, State3...>());

//4) Call the DoEvent(const Event& yourEvent) method and pass the event you want to execute
	//m_GameObject->GetComponent<StateMachineComponent>().DoEvent(DoCloseEvent{});

//EXAMPLE:
//--------------------
//* EVENTS *
//struct DoCloseEvent{};
//struct DoOpenEvent{};
//
////* STATES *
//struct StateClosed
//{
//	dae::TransitionToState<StateOpen> DoEvent(const DoOpenEvent&)
//	{
//		return{};
//	}
//	dae::DoNothing DoEvent(const DoCloseEvent&)
//	{
//		return{}; // return the DoNothing meaning nothing will happen when DoCloseEvent is called on a StateClosed
//	}
//};
//
//struct StateOpen
//{
//	dae::TransitionToState<StateClosed> DoEvent(const DoCloseEvent&)
//	{
//		return{};
//	}
//	dae::DoNothing DoEvent(const DoOpenEvent&)
//	{
//		return{}; // return the DoNothing meaning nothing will happen when DoCloseEvent is called on a StateClosed
//	}
//};

