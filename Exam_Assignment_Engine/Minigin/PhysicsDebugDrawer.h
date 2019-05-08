#pragma once
#include "Singleton.h"

namespace dae
{

	class PhysicsDebugDrawer final : public Singleton<PhysicsDebugDrawer>
	{
	public:
		PhysicsDebugDrawer() = default;
		~PhysicsDebugDrawer() = default;

		/// Draw a closed polygon provided in CCW order.
		 void DrawPolygon(b2Vec2* vertices, int vertexCount  = 8);

		/// Draw a circle.
		 void DrawCircle(const b2Vec2& center, float radius);

		/// Draw a line segment.
		 void DrawSegment(const b2Vec2& p1, const b2Vec2& p2);

		 void DrawPoint(const b2Vec2& p1, float size);
	};

}
