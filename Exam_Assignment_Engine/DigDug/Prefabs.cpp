#include "pch.h"
#include "Prefabs.h"
#include "Components.h"
#include "CollisionResponses.h"
#include "States.h"
#include "InputResponses.h"
#include "DigDugCharacter.h"
#include "SceneManager.h"

//this examples makes a box at the bottom of the screen and holds the backgroundSprite
dae::GameObject* DigDug::Setup()
{
	m_GameObject->SetName(L"DigDug");

	m_GameObject->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_dynamicBody));
	m_GameObject->AddComponent(new dae::ColliderComponent(m_GameObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(25, 25, dae::ShapeSettings(false, 1, 0.5f, 0));

	m_GameObject->AddComponent(new dae::AnimatedSpriteComponent("DD_Movement.png", 4, 2));
	m_GameObject->GetComponent<dae::AnimatedSpriteComponent>()->SetScale({ 1.6f,1.6f });
	m_GameObject->AddComponent(new dae::InputComponent(0, true));

	//INPUT ACTIONS
	std::vector<dae::InputResponse*> inputResponses;
	inputResponses.push_back(new MoveController());
	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(inputResponses.back(), dae::ControllerInput::JoyStickLeft);
	inputResponses.push_back(new MoveUpKey());
	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(inputResponses.back(), SDLK_w);
	inputResponses.push_back(new MoveLeftKey());
	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(inputResponses.back(), SDLK_a);
	inputResponses.push_back(new MoveDownKey());
	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(inputResponses.back(), SDLK_s);
	inputResponses.push_back(new MoveRightKey());
	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(inputResponses.back(), SDLK_d);

	//RUN ANIMATIONS
	auto animCmp = m_GameObject->GetComponent<dae::AnimatedSpriteComponent>();
	animCmp->AddAnimation({ L"RunNoWeapon", 1,1,1,2,0.15f });
	animCmp->AddAnimation({ L"RunWeapon", 1,1,3,4,0.15f }, false);

	m_GameObject->GetComponent<dae::ColliderComponent>()->AddCollisionResponse(new DigDugCollision());


	m_GameObject->AddComponent(new dae::StateMachineComponent());
	auto sm = m_GameObject->GetComponent<dae::StateMachineComponent>();
	sm->AddState(L"Idle", new StateIdle(), true);
	sm->AddState(L"Running", new StateRunning(), false);
	for (auto& resp : inputResponses)
	{
		sm->AddStateToStateTransition(L"Idle", L"Running", resp, true); //add trans from idle to run when any movement input is pressed
		sm->AddStateToStateTransition(L"Running", L"Idle", resp, false); //add trans from run to idle when any movement input is released
	}

	m_GameObject->AddComponent(new dae::ScriptComponent(new DigDugCharacter()));
	return m_GameObject;
}

dae::GameObject* Pooka::Setup()
{
	m_GameObject->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_kinematicBody));
	m_GameObject->AddComponent(new dae::ColliderComponent(m_GameObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(25, 25, dae::ShapeSettings(false, 1, 0.5f, 0));

	m_GameObject->AddComponent(new dae::AnimatedSpriteComponent("DD_Movement.png", 4, 2));
	m_GameObject->GetComponent<dae::AnimatedSpriteComponent>()->SetScale({ 1.6f,1.6f });

	//RUN ANIMATIONS
	auto animCmp = m_GameObject->GetComponent<dae::AnimatedSpriteComponent>();
	animCmp->AddAnimation({ L"RunNoWeapon", 1,1,1,2,0.15f });
	animCmp->AddAnimation({ L"RunWeapon", 1,1,3,4,0.15f }, false);

	m_GameObject->GetComponent<dae::ColliderComponent>()->AddCollisionResponse(new DigDugCollision());


	m_GameObject->AddComponent(new dae::StateMachineComponent());
	auto sm = m_GameObject->GetComponent<dae::StateMachineComponent>();
	sm->AddState(L"Idle", new StateIdle(), true);
	sm->AddState(L"Running", new StateRunning(), false);

	m_GameObject->AddComponent(new dae::ScriptComponent(new DigDugCharacter()));

	m_GameObject->AddComponent(new dae::AiComponent(50, dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1], L"DigDug"));

	return m_GameObject;
}