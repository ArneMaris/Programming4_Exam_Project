#pragma once
#include "GameObject.h"

namespace dae
{
	enum class NotifyEvent
	{
		CollisionStart,
		CollisionEnd,
		InputPressed,
		InputReleased,
		AnimationResponseTriggered,
		none
	};

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		virtual void OnNotify(const NotifyEvent& notifyEvent, int notifierResponseId) = 0;
	};
}