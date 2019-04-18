#pragma once
#include "Singleton.h"

namespace dae
{
	class GameInfo final : public Singleton<GameInfo>
	{
	public:
		static float deltaTime;
		static float fixedTime;
		static int windowWidth;
		static int windowHeight;
		static int physicsVelocityIterations;
		static int physicsPositionIterations;
	private:
	};
};