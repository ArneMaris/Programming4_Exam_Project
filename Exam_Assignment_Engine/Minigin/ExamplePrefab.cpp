#include "MiniginPCH.h"
#include "ExamplePrefab.h"
#include "Components.h"
#include "CollisionResponseExample.h"

//this examples makes a box at the bottom of the screen and holds the backgroundSprite
dae::GameObject* ExamplePrefab::Setup()
{
	m_GameObject->AddComponent(new dae::SpriteComponent(L"background.jpg"));
	m_GameObject->GetTransform()->SetPosition(0, 40);
	m_GameObject->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_staticBody));
	m_GameObject->AddComponent(new dae::ColliderComponent(m_GameObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(600, 20, dae::ShapeSettings(false, 1, 0.5f, 0));
	//m_GameObject->GetComponent<dae::ColliderComponent>()->AddSVGCollision(L"Test.svg", true, dae::ShapeSettings(false, 1, 0.5f, 0));
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddCollisionResponse(new CollisionResponseExample());
	m_GameObject->SetRenderOrder(4);
	return m_GameObject;
}
