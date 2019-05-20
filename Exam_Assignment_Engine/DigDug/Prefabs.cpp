#include "pch.h"
#include "Prefabs.h"
#include "Components.h"
#include "CollisionResponses.h"
#include "DigDugStates.h"
#include "InputResponses.h"
#include "DigDugCharacter.h"
#include "SceneManager.h"
#include "EnemyStates.h"

//this examples makes a box at the bottom of the screen and holds the backgroundSprite
dae::GameObject* DigDug::Setup()
{
	m_GameObject->SetName(L"DigDug");

	m_GameObject->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_dynamicBody));
	m_GameObject->AddComponent(new dae::ColliderComponent(m_GameObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(25, 25, dae::ShapeSettings(false, 1, 0.5f, 0));

	m_GameObject->AddComponent(new dae::AnimatedSpriteComponent("DigDugSprites.png", 4, 4));
	m_GameObject->GetComponent<dae::AnimatedSpriteComponent>()->SetScale({ 1.6f,1.6f });
	m_GameObject->AddComponent(new dae::InputComponent(0, true));

	//INPUT ACTIONS
	std::vector<dae::InputResponse*> moveResponses;
	moveResponses.push_back(new MoveController());
	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(moveResponses.back(), dae::ControllerInput::JoyStickLeft);
	moveResponses.push_back(new MoveUpKey());
	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(moveResponses.back(), SDLK_w);
	moveResponses.push_back(new MoveLeftKey());
	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(moveResponses.back(), SDLK_a);
	moveResponses.push_back(new MoveDownKey());
	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(moveResponses.back(), SDLK_s);
	moveResponses.push_back(new MoveRightKey());
	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(moveResponses.back(), SDLK_d);


	auto animCmp = m_GameObject->GetComponent<dae::AnimatedSpriteComponent>();
	animCmp->AddAnimation({ L"RunNoWeapon", 1,1,1,2,0.15f }, true);
	animCmp->AddAnimation({ L"RunWeapon", 1,1,3,4,0.15f }, false);
	animCmp->AddAnimation({ L"Idle", 3,3,4,4,1 }, false);
	animCmp->AddAnimation({ L"Pump", 2,2,1,2,0.15f }, false);
	animCmp->AddAnimation({ L"DieStone", 3,3,1,3,0.15f }, false);
	animCmp->AddAnimation({ L"DieEnemy", 4,4,1,4,0.15f }, false);

	auto collResp = new DigDugCollision();
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddCollisionResponse(collResp);


	m_GameObject->AddComponent(new dae::StateMachineComponent());
	auto sm = m_GameObject->GetComponent<dae::StateMachineComponent>();
	sm->AddState(L"Idle", new DigDugStates::Idle(), true);
	sm->AddState(L"Run", new DigDugStates::Run(), false);
	sm->AddState(L"Dead", new DigDugStates::Dead(), false);
	for (auto& resp : moveResponses)
	{
		sm->AddStateToStateTransition(L"Idle", L"Run", resp, true); //add trans from idle to run when any movement input is pressed
		sm->AddStateToStateTransition(L"Run", L"Idle", resp, false); //add trans from run to idle when any movement input is released
	}
	sm->AddToStateTransition(L"Dead", collResp, true);

	m_GameObject->AddComponent(new dae::ScriptComponent(new DigDugCharacter()));
	return m_GameObject;
}

dae::GameObject* Pooka::Setup()
{
	float moveSpeed{ 50 };

	//put all enemies in layer 1 for easier collision checks ;D
	m_GameObject->SetLayer(1);

	m_GameObject->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_kinematicBody));
	m_GameObject->AddComponent(new dae::ColliderComponent(m_GameObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(20, 20, dae::ShapeSettings(true, 1, 0.5f, 0));

	auto colResponse = new EnemyCollision();
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddCollisionResponse(colResponse);

	m_GameObject->AddComponent(new dae::AnimatedSpriteComponent("PookaFygarMovementSquash.png", 5, 2));
	m_GameObject->GetComponent<dae::AnimatedSpriteComponent>()->SetScale({ 1.6f,1.6f });


	auto animCmp = m_GameObject->GetComponent<dae::AnimatedSpriteComponent>();
	animCmp->AddAnimation({ L"Run", 1,1,1,2,0.15f });
	animCmp->AddAnimation({ L"Ghost", 1,1,3,4,0.15f }, false);
	animCmp->AddAnimation({ L"DieStone", 1,1,5,5,1 }, false);

	animCmp->AddAnimation({ L"BlowUp", 1,1,1,4,0.5f }, false);


	m_GameObject->AddComponent(new dae::StateMachineComponent());
	auto sm = m_GameObject->GetComponent<dae::StateMachineComponent>();
	sm->AddState(L"Run", new EnemyStates::Run(), true);
	sm->AddState(L"Ghost", new EnemyStates::Ghost(), false);
	sm->AddState(L"BlowUpOne", new EnemyStates::BlowUpOne(), false);
	sm->AddState(L"BlowUpTwo", new EnemyStates::BlowUpTwo(), false);
	sm->AddState(L"BlowUpThree", new EnemyStates::BlowUpThree(), false);
	sm->AddState(L"Pop", new EnemyStates::Pop(), false);

	sm->AddStateToStateTransition(L"Run", L"BlowUpOne", colResponse, true);
	sm->AddStateToStateTransition(L"BlowUpOne", L"BlowUpTwo", colResponse, true);
	sm->AddStateToStateTransition(L"BlowUpTwo", L"BlowUpThree", colResponse, true);
	sm->AddStateToStateTransition(L"BlowUpThree", L"Pop", colResponse, true);

	m_GameObject->AddComponent(new dae::AiComponent(moveSpeed, dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1], L"DigDug"));

	return m_GameObject;
}