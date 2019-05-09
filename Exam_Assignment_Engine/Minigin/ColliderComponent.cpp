#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "PhysicsDebugDrawer.h"
#include "CollisionResponse.h"

dae::ColliderComponent::ColliderComponent(PhysicsBodyComponent* physicsBody)
	:m_pBodyRef{ physicsBody->GetPhysicsBody() }
{
	Logger::GetInstance().LogInfo(L"ColliderComponent created, you can add Collision/trigger(shapes) by doing Add...()");
	m_pSceneRef = SceneManager::GetInstance().GetActiveScene();
	if (m_pBodyRef == nullptr)
	{
		Logger::GetInstance().LogWarning(L"Trying to add a colliderComponent to an invalid physicsBody!");
	}
}

dae::ColliderComponent::~ColliderComponent()
{
	for (auto& resp : m_CollisionResponses)
	{
		delete resp;
	}
	m_CollisionResponses.clear();
}

void dae::ColliderComponent::Update()
{

}

void dae::ColliderComponent::Initialize()
{

}

void dae::ColliderComponent::Render() const
{

}

void dae::ColliderComponent::PostRender() const
{
	if (GameInfo::drawPhysicsDebug)
	{
		PhysicsDebugDrawer::GetInstance().DrawPoint(m_pGameObject->GetTransform()->GetPosition());
		for (size_t i = 0; i < m_Fixtures.size(); i++)
		{
			switch (m_Fixtures[i]->GetShape()->GetType())
			{
			case b2Shape::Type::e_polygon:
				PhysicsDebugDrawer::GetInstance().DrawPolygon(m_pGameObject, static_cast<b2PolygonShape*>(m_Fixtures[i]->GetShape())->m_vertices, static_cast<b2PolygonShape*>(m_Fixtures[i]->GetShape())->m_count);
				break;
			case b2Shape::Type::e_circle:
				PhysicsDebugDrawer::GetInstance().DrawCircle(m_pGameObject, static_cast<b2CircleShape*>(m_Fixtures[i]->GetShape())->m_p, static_cast<b2CircleShape*>(m_Fixtures[i]->GetShape())->m_radius);
				break;
			case b2Shape::Type::e_chain:
				PhysicsDebugDrawer::GetInstance().DrawPolygon(m_pGameObject, static_cast<b2ChainShape*>(m_Fixtures[i]->GetShape())->m_vertices, static_cast<b2ChainShape*>(m_Fixtures[i]->GetShape())->m_count);
				break;
			case b2Shape::Type::e_edge:
				PhysicsDebugDrawer::GetInstance().DrawSegment(m_pGameObject, static_cast<b2EdgeShape*>(m_Fixtures[i]->GetShape())->m_vertex1, static_cast<b2EdgeShape*>(m_Fixtures[i]->GetShape())->m_vertex2);
				break;
			}
		}
	}
}


void dae::ColliderComponent::AddBoxShape(float height, float width, const ShapeSettings& shapeSettings)
{
	AddBoxShape(height, width, { 0,0 }, 0, shapeSettings);
}

void dae::ColliderComponent::AddBoxShape(float height, float width, const b2Vec2& relativePos, float rot, const ShapeSettings& shapeSettings)
{
	if (m_pBodyRef == nullptr)
	{
		Logger::GetInstance().LogWarning(L"Trying to add a shape to an invalid PhysicsBody!");
		return;
	}
	b2PolygonShape shape;
	shape.m_type = shape.e_polygon;
	shape.SetAsBox(height/2, width/2, relativePos, rot);
	CreateFixture(shape, shapeSettings);
}

void dae::ColliderComponent::AddCircleShape(const b2Vec2& relativePos, float radius, const ShapeSettings& shapeSettings)
{
	if (m_pBodyRef == nullptr)
	{
		Logger::GetInstance().LogWarning(L"Trying to add a shape to an invalid PhysicsBody!");
		return;
	}
	b2CircleShape shape;
	shape.m_type = shape.e_circle;
	shape.m_p = relativePos;
	shape.m_radius = radius;
	CreateFixture(shape, shapeSettings);

}

void dae::ColliderComponent::AddEdgeShape(const b2Vec2& beginPos, const b2Vec2& endPos, const ShapeSettings& shapeSettings)
{
	if (m_pBodyRef == nullptr)
	{
		Logger::GetInstance().LogWarning(L"Trying to add a shape to an invalid PhysicsBody!");
		return;
	}
	b2EdgeShape shape;
	shape.m_type = shape.e_edge;
	shape.Set(beginPos, endPos);
	CreateFixture(shape, shapeSettings);
}

void dae::ColliderComponent::AddPolygonShape(const std::vector<b2Vec2>& vertices, const ShapeSettings& shapeSettings)
{
	if (m_pBodyRef == nullptr)
	{
		Logger::GetInstance().LogWarning(L"Trying to add a shape to an invalid PhysicsBody!");
		return;
	}
	if (vertices.size() > 8)
	{
		Logger::GetInstance().LogWarning(L"More than 8 vertices so they will be ignored, PolygonShapes only support up to 8 vertices!");
	}
	else if (vertices.size() < 3)
	{
		Logger::GetInstance().LogWarning(L"Less than 3 vertices, shape NOT added!");
		return;
	}

	b2PolygonShape shape;
	shape.m_type = shape.e_polygon;
	shape.Set(vertices.data(), vertices.size());

	CreateFixture(shape, shapeSettings);
}

void dae::ColliderComponent::AddChainShape(const std::vector<b2Vec2>& vertices, bool closedLoop, const ShapeSettings& shapeSettings)
{
	if (m_pBodyRef == nullptr)
	{
		Logger::GetInstance().LogWarning(L"Trying to add a shape to an invalid PhysicsBody!");
		return;
	}
	if (vertices.size() < 3)
	{
		Logger::GetInstance().LogWarning(L"Not enough vertices! Add atleast 3 vertices to your vector, if you need only 2 use: AddEdgeShape()!");
		return;
	}

	b2ChainShape shape;
	shape.m_type = shape.e_chain;
	if (closedLoop)
		shape.CreateLoop(vertices.data(), vertices.size());
	else
		shape.CreateChain(vertices.data(), vertices.size());

	CreateFixture(shape, shapeSettings);
}

void dae::ColliderComponent::AddSVGCollision(const std::wstring & svgFilePath, bool closedLoop, const ShapeSettings & shapeSettings)
{
	AddChainShape(ResourceManager::GetInstance().GetVerticesFromSVG(svgFilePath), closedLoop, shapeSettings);
}

std::vector<b2Fixture*> dae::ColliderComponent::GetFixturesVector() const
{
	if (m_Fixtures.size() <= 0)
	{
		Logger::GetInstance().LogError(L"Trying to get an empty fixtureVector");
	}
	return m_Fixtures;
}

void dae::ColliderComponent::RemoveShape(int creationOrder)
{
	m_pBodyRef->DestroyFixture(m_Fixtures[creationOrder - 1]);
	auto it = std::find(m_Fixtures.begin(), m_Fixtures.end(), m_Fixtures[creationOrder-1]);
	if (it != m_Fixtures.end())
	{
		it = m_Fixtures.erase(it);
	}
	else
	{
		Logger::GetInstance().LogWarning(L"Trying to remove a non existing shape!");
	}
}

void dae::ColliderComponent::AddCollisionResponse(CollisionResponse* collResponse)
{
	if (std::find_if(m_CollisionResponses.begin(), m_CollisionResponses.end(),
		[collResponse](CollisionResponse* collR) {return collResponse == collR; }) == m_CollisionResponses.end())
	{
		m_CollisionResponses.push_back(collResponse);
		collResponse->SetOwnerObject(m_pGameObject);
	}
	else
	{
		Logger::GetInstance().LogWarning(L"Already added this collision response to the ColliderComponent");
	}
}

void dae::ColliderComponent::RemoveCollisionResponse(CollisionResponse* collResponse)
{
	for (auto& collR : m_CollisionResponses)
	{
		if (collR == collResponse)
		{
			delete collR;
			collR = nullptr;
		}
	}
	m_CollisionResponses.erase(std::remove(m_CollisionResponses.begin(), m_CollisionResponses.end(), nullptr), m_CollisionResponses.end());
}

std::vector<dae::CollisionResponse*> dae::ColliderComponent::GetAllCollisionResponses() const
{
	return m_CollisionResponses;
}

void dae::ColliderComponent::StartCollisionWith(GameObject * collisionObj)
{
	for (auto colR : m_CollisionResponses)
	{
		colR->OnCollisionStart(collisionObj);
	}
}

void dae::ColliderComponent::EndCollisionWith(GameObject * collisionObj)
{
	for (auto colR : m_CollisionResponses)
	{
		colR->OnCollisionEnd(collisionObj);
	}
}

void dae::ColliderComponent::CreateFixture(const b2Shape& shape, const ShapeSettings& shapeSettings)
{
	b2FixtureDef fixDef{};
	fixDef.shape = &shape;
	fixDef.density = shapeSettings.density;
	fixDef.friction = shapeSettings.friction;
	fixDef.restitution = shapeSettings.restitution;
	fixDef.isSensor = shapeSettings.isTrigger;
	m_Fixtures.push_back(m_pBodyRef->CreateFixture(&fixDef));
	m_Fixtures.back()->SetUserData(this); //set the user data to the ColliderComponent so that in the callbacks you can acces it
}
