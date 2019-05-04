#pragma once
#include "BaseComponent.h"
#include "PhysicsBodyComponent.h"

namespace dae
{
	class Scene;

	class ColliderComponent final: public BaseComponent
	{
	public:
		struct ShapeSettings
		{
			float density;
			float friction;
			float restitution;
			bool isTrigger;

			ShapeSettings(bool IsTrigger, float Density, float Friction, float Restitution)
				:isTrigger{IsTrigger}
				,density{Density}
				,friction{Friction}
				,restitution{Restitution}
			{}

			ShapeSettings()
				:isTrigger{ false }
				, density{ 1 }
				, friction{ 0.5f }
				, restitution{ 0.1f }
			{}
		};
		explicit ColliderComponent(PhysicsBodyComponent* physicsBodyComp);
		~ColliderComponent() = default;
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

		std::vector<std::shared_ptr<b2Fixture>> GetFixturesVector() const;
		void RemoveShape(int creationOrder = 1);

	protected:
		virtual void Update() override;

	private:
		b2Body* m_pBodyRef;
		std::vector<std::shared_ptr<b2Fixture>> m_Fixtures;
		b2ContactListener* m_pContactListener;

		Scene* m_pSceneRef;

		void CreateFixture(const b2Shape & shape, const ShapeSettings& shapeSettings);
	};

}
