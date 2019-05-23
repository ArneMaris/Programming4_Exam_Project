#include "pch.h"
#include "Prefabs.h"
#include "Components.h"
#include "CollisionResponses.h"
#include "DigDugStates.h"
#include "InputResponses.h"
#include "DigDugCharacter.h"
#include "SceneManager.h"
#include "EnemyStates.h"
#include "AnimationResponse.h"
#include "GridLevel.h"
#include "DigDugLevel.h"

//this examples makes a box at the bottom of the screen and holds the backgroundSprite
void DigDug::Setup()
{
	m_GameObject->SetName(L"DigDug");

	m_GameObject->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_dynamicBody));
	m_GameObject->AddComponent(new dae::ColliderComponent(m_GameObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(20, 20, dae::ShapeSettings(false, 1, 0.5f, 0));

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


	m_GameObject->GetComponent<dae::InputComponent>()->AddInputAction(new Pump(), SDLK_SPACE);

	auto animCmp = m_GameObject->GetComponent<dae::AnimatedSpriteComponent>();
	animCmp->AddAnimation({ L"Idle", 3,3,4,4,1 }, true);
	animCmp->AddAnimation({ L"RunWeapon", 1,1,3,4,0.15f }, false);
	animCmp->AddAnimation({ L"RunNoWeapon", 1,1,1,2,0.15f }, false);
	animCmp->AddAnimation({ L"Pump", 2,2,1,2,0.15f }, false);
	animCmp->AddAnimation({ L"DieStone", 3,3,1,3,0.15f }, false);
	animCmp->AddAnimation({ L"DieEnemy", 4,4,1,4,0.25f }, false);
	animCmp->AddAnimation({ L"Gone", 2,2,3,4,1 }, false);

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

}

void Pooka::Setup()
{
	float moveSpeed{ 50 };

	static_cast<DigDugLevel*>(dae::SceneManager::GetInstance().GetActiveScene())->AddEnemy();

	//put all enemies in layer 1 for easier collision checks ;D
	m_GameObject->SetLayer(1);
	m_GameObject->SetName(L"Pooka");

	m_GameObject->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_kinematicBody));
	m_GameObject->AddComponent(new dae::ColliderComponent(m_GameObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(16, 16, dae::ShapeSettings(true, 0.5f, 0.5f, 0));

	auto colResponse = new EnemyCollision();
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddCollisionResponse(colResponse);

	m_GameObject->AddComponent(new dae::AnimatedSpriteComponent("PookaFygar.png", 5, 5));
	m_GameObject->GetComponent<dae::AnimatedSpriteComponent>()->SetScale({ 1.6f,1.6f });


	auto animCmp = m_GameObject->GetComponent<dae::AnimatedSpriteComponent>();
	animCmp->AddAnimation({ L"Run", 1,1,1,2,0.15f });
	animCmp->AddAnimation({ L"Ghost", 1,1,3,4,0.15f }, false);
	animCmp->AddAnimation({ L"DieStone", 1,1,5,5,1 }, false);

	animCmp->AddAnimation({ L"BlowUpOne", 3,3,1,1,5}, false);
	animCmp->AddAnimation({ L"BlowUpTwo", 3,3,2,2,5 }, false);
	animCmp->AddAnimation({ L"BlowUpThree", 3,3,3,3,5 }, false);
	animCmp->AddAnimation({ L"Pop", 3,3,4,5,1 }, false);


	m_GameObject->AddComponent(new dae::StateMachineComponent());
	auto sm = m_GameObject->GetComponent<dae::StateMachineComponent>();
	sm->AddState(L"Run", new EnemyStates::Run(), true);
	sm->AddState(L"Ghost", new EnemyStates::Ghost(), false);
	sm->AddState(L"BlowUpOne", new EnemyStates::BlowUpOne(), false);
	sm->AddState(L"BlowUpTwo", new EnemyStates::BlowUpTwo(), false);
	sm->AddState(L"BlowUpThree", new EnemyStates::BlowUpThree(), false);
	sm->AddState(L"Pop", new EnemyStates::Pop(), false);

	sm->AddStateToStateTransition(L"BlowUpThree", L"Pop", colResponse, true);
	sm->AddStateToStateTransition(L"BlowUpTwo", L"BlowUpThree", colResponse, true);
	sm->AddStateToStateTransition(L"BlowUpOne", L"BlowUpTwo", colResponse, true);
	sm->AddStateToStateTransition(L"Run", L"BlowUpOne", colResponse, true);

	m_GameObject->AddComponent(new dae::AiComponent(moveSpeed, dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1], L"DigDug"));

}

void Fygar::Setup()
{
	float moveSpeed{ 30 };

	static_cast<DigDugLevel*>(dae::SceneManager::GetInstance().GetActiveScene())->AddEnemy();

	//put all enemies in layer 1 for easier collision checks ;D
	m_GameObject->SetLayer(1);
	m_GameObject->SetName(L"Fygar");

	m_GameObject->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_kinematicBody));
	m_GameObject->AddComponent(new dae::ColliderComponent(m_GameObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(18, 18, dae::ShapeSettings(true, 0.5f, 0.5f, 0));

	auto colResponse = new EnemyCollision();
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddCollisionResponse(colResponse);

	m_GameObject->AddComponent(new dae::AnimatedSpriteComponent("PookaFygar.png", 5, 5));
	m_GameObject->GetComponent<dae::AnimatedSpriteComponent>()->SetScale({ 1.6f,1.6f });


	auto animCmp = m_GameObject->GetComponent<dae::AnimatedSpriteComponent>();
	animCmp->AddAnimation({ L"Run", 2,2,1,2,0.15f });
	animCmp->AddAnimation({ L"Ghost", 2,2,3,4,0.15f }, false);
	animCmp->AddAnimation({ L"DieStone", 2,2,5,5,1 }, false);

	animCmp->AddAnimation({ L"BlowUpOne", 4,4,1,1,5 }, false);
	animCmp->AddAnimation({ L"BlowUpTwo", 4,4,2,2,5 }, false);
	animCmp->AddAnimation({ L"BlowUpThree", 4,4,3,3,5 }, false);
	animCmp->AddAnimation({ L"Pop", 4,4,4,5,1 }, false);

	dae::AnimationResponse* flameResponse = new dae::AnimationResponse( 5,5,true );
	dae::Animation fygarAttack{ L"FygarAttack", 5,5,1,5,0.2f, flameResponse };
	animCmp->AddAnimation(fygarAttack, false);

	m_GameObject->AddComponent(new dae::StateMachineComponent());
	auto sm = m_GameObject->GetComponent<dae::StateMachineComponent>();
	sm->AddState(L"Run", new EnemyStates::Run(), true);
	sm->AddState(L"Ghost", new EnemyStates::Ghost(), false);
	sm->AddState(L"BlowUpOne", new EnemyStates::BlowUpOne(), false);
	sm->AddState(L"BlowUpTwo", new EnemyStates::BlowUpTwo(), false);
	sm->AddState(L"BlowUpThree", new EnemyStates::BlowUpThree(), false);
	sm->AddState(L"Pop", new EnemyStates::Pop(), false);
	sm->AddState(L"Attacking", new EnemyStates::Attacking(), false);

	sm->AddStateToStateTransition(L"BlowUpThree", L"Pop", colResponse, true);
	sm->AddStateToStateTransition(L"BlowUpTwo", L"BlowUpThree", colResponse, true);
	sm->AddStateToStateTransition(L"BlowUpOne", L"BlowUpTwo", colResponse, true);
	sm->AddStateToStateTransition(L"Run", L"BlowUpOne", colResponse, true);

	sm->AddToStateTransition(L"Attacking", flameResponse, true);
	sm->AddStateToStateTransition(L"Attacking", L"Run", flameResponse, true);
	m_GameObject->AddComponent(new dae::AiComponent(moveSpeed, dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1], L"DigDug"));

}

void FygarFlame::Setup()
{
	auto level = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1];
	m_GameObject->SetLayer(1);
	m_GameObject->GetTransform()->SetPosition(m_Pos);
	m_GameObject->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_staticBody));
	m_GameObject->AddComponent(new dae::ColliderComponent(m_GameObject->GetComponent<dae::PhysicsBodyComponent>()));
	if (m_Flip != SDL_FLIP_HORIZONTAL)
	{
		m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(20, 40, { 40,0 }, 0, dae::ShapeSettings(true, 0.1f, 0.5f, 0));
		if (level->GetTileByPos({ m_Pos.x + level->GetTileWidth(), m_Pos.y })->GetIsWalkable()
			&& level->GetTileByPos({ m_Pos.x + level->GetTileWidth() * 2, m_Pos.y })->GetIsWalkable())
		{
			m_GameObject->SetLifeTime(0.45f);
		}
		else
		{
			m_GameObject->MarkForDelete();
			return;
		}
	}
	else
	{
		m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(20, 40, { -40,0 },0, dae::ShapeSettings(true, 0.1f, 0.5f, 0));
		if (level->GetTileByPos({ m_Pos.x - level->GetTileWidth(), m_Pos.y })->GetIsWalkable()
			&& level->GetTileByPos({ m_Pos.x - level->GetTileWidth() * 2, m_Pos.y })->GetIsWalkable())
		{
			m_GameObject->SetLifeTime(0.45f);
		}
		else
		{
			m_GameObject->MarkForDelete();
			return;
		}
	}

	m_GameObject->AddComponent(new dae::AnimatedSpriteComponent("FygarFlame.png", 3, 1, 0.15f));
	m_GameObject->GetComponent<dae::AnimatedSpriteComponent>()->SetScale({ 1.6f,1.6f });
	m_GameObject->GetComponent<dae::AnimatedSpriteComponent>()->SetSpriteOffset({ 45,0 });
	m_GameObject->GetComponent<dae::AnimatedSpriteComponent>()->SetFlipDirection(m_Flip);
}

void Stone::Setup()
{
	m_GameObject->SetLayer(3);
	//m_GameObject->SetLifeTime(0.44f);
	m_GameObject->AddComponent(new dae::PhysicsBodyComponent(b2BodyType::b2_staticBody));
	m_GameObject->AddComponent(new dae::ColliderComponent(m_GameObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_GameObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(26, 26, dae::ShapeSettings(false, 1, 0.8f, 0.2f));

	m_GameObject->AddComponent(new dae::AnimatedSpriteComponent("Stone.png", 2, 2, 0.15f));
	auto animComp = m_GameObject->GetComponent<dae::AnimatedSpriteComponent>();
	animComp->SetScale({ 1.6f,1.6f });
	animComp->SetPaused(true);
	animComp->AddAnimation({ L"Losen",1,1,1,2,0.15f });
	animComp->AddAnimation({ L"Break",2,2,1,2,0.15f }, false);
}