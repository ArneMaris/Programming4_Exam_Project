#pragma once
#include "Singleton.h"

namespace dae
{
	class GameInfo final : public Singleton<GameInfo>
	{
	public:
		static float deltaTime;
		static float fixedTime;
		const static int windowWidth;
		const static int windowHeight;
		static int physicsVelocityIterations;
		static int physicsPositionIterations;
		static bool enableVsync;
		static bool drawPhysicsDebug;

		static int amountOfGameObjects;
	private:
	};
};