#pragma once

namespace dae
{
	class GameInfo final
	{
	public:
		static float deltaTime;
		static float fixedTime;
		static int windowWidth;
		static int windowHeight;
		static int physicsVelocityIterations;
		static int physicsPositionIterations;
		static bool enableVsync;
		static bool drawPhysicsDebug;

		static int amountOfGameObjects;
		static int amountOfResponses;

		static bool gameEnded;
	};
};