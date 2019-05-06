#pragma once
#include "Box2D/Common/b2Draw.h"

namespace dae
{

	class PhysicsDebugDrawer : public b2Draw
	{
	public:
		PhysicsDebugDrawer() = default;
		~PhysicsDebugDrawer() = default;

		///// Draw a closed polygon provided in CCW order.
		//virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

		///// Draw a solid closed polygon provided in CCW order.
		//virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

		///// Draw a circle.
		//virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

		///// Draw a solid circle.
		//virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

		///// Draw a line segment.
		//virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	};

}
