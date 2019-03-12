#pragma once
#include "Singleton.h"

namespace dae
{
	class GameInfo final : public Singleton<GameInfo>
	{
	public:
		GameInfo();
		static float deltaTime;
		static float fixedTime;
	private:
	};
};