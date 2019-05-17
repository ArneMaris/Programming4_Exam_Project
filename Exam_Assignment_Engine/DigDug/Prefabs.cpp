#include "pch.h"
#include "Prefabs.h"
#include "Components.h"
#include "CollisionResponses.h"
#include "States.h"
#include "InputResponses.h"
#include "DigDugCharacter.h"

//this examples makes a box at the bottom of the screen and holds the backgroundSprite
dae::GameObject* DigDug::Setup()
{
	m_GameObject->SetName(L"DigDug");

	m_GameObject->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_kinematicBody));
	m_GameObject->AddComponent(new dae::ColliderComponent(m_GameObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(25, 25, dae::ShapeSettings(false, 1, 0.5f, 0));

	m_GameObject->AddComponent(new dae::AnimatedSpriteComponent(L"DD_Movement.png", 4, 2));
	m_GameObject->GetComponent<dae::AnimatedSpriteComponent>()->SetScale(2);
	m_GameObject->AddComponent(new dae::InputComponent(0, false));

	//INPUT ACTIONS
	auto moveResponse = new Move();
	moveResponse->SetOwnerObject(m_GameObject);
	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(moveResponse, dae::ControllerInput::JoyStickLeft);

	//RUN ANIMATIONS
	auto animCmp = m_GameObject->GetComponent<dae::AnimatedSpriteComponent>();
	animCmp->AddAnimation({ L"RunHorizontalNoWeapon", 1,1,1,2,0.2f });
	animCmp->AddAnimation({ L"RunHorizontalWeapon", 1,1,3,4,0.2f });
	animCmp->AddAnimation({ L"RunVerticalNoWeapon", 2,2,1,2,0.2f });
	animCmp->AddAnimation({ L"RunVerticalWeapon", 2,2,3,4,0.2f });

	auto collResp = new CollisionResponseExample2;
	collResp->SetOwnerObject(m_GameObject);
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddCollisionResponse(collResp);


	m_GameObject->AddComponent(new dae::StateMachineComponent());

	auto sm = m_GameObject->GetComponent<dae::StateMachineComponent>();
	sm->AddState(L"Idle", new StateIdle(), true);
	sm->AddState(L"Running", new StateRunning(), false);
	sm->AddStateToStateTransition(L"Idle", L"Running", moveResponse, true); //add trans from idle to run when MoveUpCommand is pressed
	sm->AddStateToStateTransition(L"Running", L"Idle", moveResponse, false); //add trans from run to idle when MoveUpCommand is released

	return m_GameObject;
}

dae::GameObject* Background::Setup()
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