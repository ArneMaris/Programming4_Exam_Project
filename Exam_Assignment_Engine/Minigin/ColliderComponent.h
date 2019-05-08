#pragma once
#include "BaseComponent.h"
#include "PhysicsBodyComponent.h"
#include <deque>

namespace dae
{
	struct ShapeSettings
	{
		float density;
		float friction;
		float restitution;
		bool isTrigger;

		ShapeSettings(bool IsTrigger, float Density, float Friction, float Restitution)
			:isTrigger{ IsTrigger }
			, density{ Density }
			, friction{ Friction }
			, restitution{ Restitution }
		{}

		ShapeSettings()
			:isTrigger{ false }
			, density{ 1 }
			, friction{ 0.5f }
			, restitution{ 0.1f }
		{}
	};
	class Scene;

	class ColliderComponent final: public BaseComponent
	{
		friend class MMCallbacks;
	public:
		explicit ColliderComponent(PhysicsBodyComponent* physicsBody);
		~ColliderComponent();
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;
		void AddBoxShape(float height, float width, const ShapeSettings& shapeSettings);
		void AddBoxShape(float height, float width, const b2Vec2& relativePos, float rot, const ShapeSettings& shapeSettings);
		void AddCircleShape(const b2Vec2& relativePos, float radius, const ShapeSettings& shapeSettings);
		void AddEdgeShape(const b2Vec2& beginPos, const b2Vec2& endPos, const ShapeSettings& shapeSettings);
		void AddPolygonShape(const std::vector<b2Vec2>& vertices, const ShapeSettings& shapeSettings);
		void AddChainShape(const std::vector<b2Vec2>& vertices, bool closedLoop, const ShapeSettings& shapeSettings);
		void AddSVGCollision(const std::wstring& svgFilePath, bool closedLoop, const ShapeSettings& shapeSettings);

		std::vector<b2Fixture*> GetFixturesVector() const;
		void RemoveShape(int creationOrder = 1);

		std::deque<GameObject*> GetAllCollisionObjects();
		bool IsCollidingWith(GameObject* withObject);
		bool IsColliding();

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;
		virtual void PostRender() const override;
		void AddCollisionObject(GameObject* collisionObj);
		void RemoveCollisionObject(GameObject* collisionObj);

	private:

		b2Body* m_pBodyRef;
		std::vector<b2Fixture*> m_Fixtures;
		Scene* m_pSceneRef;
		void CreateFixture(const b2Shape & shape, const ShapeSettings& shapeSettings);
		std::deque<GameObject*> m_CollisionObjects;

	};

}
