#pragma once
#include "BaseComponent.h"
#include "PhysicsBodyComponent.h"
#include "CollisionResponse.h"

namespace dae
{
	//the same positive groupIndex will ALWAYS collide wich other of that groupIndex
	//the same negative groupIndex will NEVER collide wich other of that groupIndex
	struct ShapeSettings
	{
		float density;
		float friction;
		float restitution;
		bool isTrigger;
		int groupIndex;

		ShapeSettings(bool IsTrigger, float Density, float Friction, float Restitution, int groupIndex = 0)
			:isTrigger{ IsTrigger }
			, density{ Density }
			, friction{ Friction }
			, restitution{ Restitution }
			, groupIndex{ groupIndex }
		{}

		ShapeSettings()
			:isTrigger{ false }
			, density{ 1 }
			, friction{ 0.5f }
			, restitution{ 0.1f }
			, groupIndex{0}
		{}
	};
	class Scene;

	class ColliderComponent final: public BaseComponent
	{
		friend class CollisionCallbacks;
	public:
		explicit ColliderComponent(PhysicsBodyComponent* physicsBody);
		~ColliderComponent();
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		//SHAPE ADDING METHODS
		void AddBoxShape(float height, float width, const ShapeSettings& shapeSettings);
		void AddBoxShape(float height, float width, const b2Vec2& relativePos, float rot, const ShapeSettings& shapeSettings);
		void AddCircleShape(const b2Vec2& relativePos, float radius, const ShapeSettings& shapeSettings);
		void AddEdgeShape(const b2Vec2& beginPos, const b2Vec2& endPos, const ShapeSettings& shapeSettings);
		void AddPolygonShape(const std::vector<b2Vec2>& vertices, const ShapeSettings& shapeSettings);
		void AddChainShape(const std::vector<b2Vec2>& vertices, bool closedLoop, const ShapeSettings& shapeSettings);
		void AddSVGCollision(const std::string& svgFilePath, bool closedLoop, const ShapeSettings& shapeSettings);

		void RemoveShape(int creationOrder = 1);

		std::vector<b2Fixture*> GetFixturesVector() const;

		//COLLISIONMETHODS
		void AddCollisionResponse(CollisionResponse* collResponse);
		void RemoveCollisionResponse(CollisionResponse* collResponse);
		std::vector<CollisionResponse*> GetAllCollisionResponses() const;
		bool IsColliding() const {return m_Colliding;};

		void SetActive(bool value) { m_Active = value; m_Collisions = 0; };
		bool GetIsActive() const { return m_Active; };

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;
		virtual void PostRender() const override;
		void StartCollisionWith(GameObject* collisionObj);
		void EndCollisionWith(GameObject* collisionObj);

	private:
		void CreateFixture(const b2Shape & shape, const ShapeSettings& shapeSettings);

		bool m_Colliding;
		int m_Collisions;
		b2Body* m_pBodyRef;
		std::vector<b2Fixture*> m_Fixtures;

		std::vector<CollisionResponse*> m_pCollisionResponses;

		bool m_Active;
	};

}
