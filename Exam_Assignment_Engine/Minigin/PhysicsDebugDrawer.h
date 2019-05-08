#pragma once
#include "Singleton.h"
#include "GameObject.h"

namespace dae
{

	class PhysicsDebugDrawer final : public Singleton<PhysicsDebugDrawer>
	{
	public:
		PhysicsDebugDrawer() = default;
		~PhysicsDebugDrawer() = default;

		/// Draw a closed polygon provided in CCW order.
		 void DrawPolygon(GameObject* objectRef, b2Vec2* vertices, int vertexCount  = 8);

		/// Draw a circle.
		 void DrawCircle(GameObject* objectRef, const b2Vec2& center, float radius);

		/// Draw a line segment.
		 void DrawSegment(GameObject* objectRef, const b2Vec2& p1, const b2Vec2& p2);

		 void DrawPoint(const b2Vec2& p1);
	};

}
