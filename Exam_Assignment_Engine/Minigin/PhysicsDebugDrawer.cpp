#include "MiniginPCH.h"
#include "PhysicsDebugDrawer.h"
#include "Renderer.h"
#define PI 3.14159265358979323846

void dae::PhysicsDebugDrawer::DrawPolygon(GameObject* objectRef, b2Vec2* vertices, int vertexCount)
{
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 155, 255, 1);
	std::vector<SDL_Point> points;

	for (int i = 0; i < vertexCount; i++)
	{
		points.push_back({ 
			int(vertices[i].x + objectRef->GetTransform()->GetPosition().x)
			,int(GameInfo::windowHeight - (vertices[i].y + objectRef->GetTransform()->GetPosition().y)) 
			});
	}
	points.push_back(points[0]);
	SDL_RenderDrawLines(Renderer::GetInstance().GetSDLRenderer(), points.data(), vertexCount+1);
}

void dae::PhysicsDebugDrawer::DrawCircle(GameObject* objectRef, const b2Vec2 & center, float radius)
{
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 0, 255, 1);
	int sides = int(10 * radius);
	float d_a = float(PI) / sides;
	float angle = d_a;

	b2Vec2 start, end;
	end.x = radius;
	end.y = 0.0f;
	end = end + center;
	for (int i = 0; i != sides; i++)
	{
		start = end;
		end.x = cos(angle) * radius;
		end.y = sin(angle) * radius;
		end = end + center;
		angle += d_a;
		SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer()
			,int(start.x + objectRef->GetTransform()->GetPosition().x),int(GameInfo::windowHeight - (start.y + objectRef->GetTransform()->GetPosition().y))
			,int(end.x + objectRef->GetTransform()->GetPosition().x),int(GameInfo::windowHeight - (end.y + objectRef->GetTransform()->GetPosition().y)));
	}
}

void dae::PhysicsDebugDrawer::DrawSegment(GameObject* objectRef, const b2Vec2 & p1, const b2Vec2 & p2)
{
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 255, 255, 1);
	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), 
		int(p1.x + objectRef->GetTransform()->GetPosition().x), int(GameInfo::windowHeight - (p1.y + objectRef->GetTransform()->GetPosition().y)),
		int(p2.x + objectRef->GetTransform()->GetPosition().x), int(GameInfo::windowHeight - (p2.y + objectRef->GetTransform()->GetPosition().y)));
}

void dae::PhysicsDebugDrawer::DrawPoint(const b2Vec2 & p)
{
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 1);
	SDL_RenderDrawPoint(Renderer::GetInstance().GetSDLRenderer(), 
		int(p.x), int(GameInfo::windowHeight - p.y));
}
