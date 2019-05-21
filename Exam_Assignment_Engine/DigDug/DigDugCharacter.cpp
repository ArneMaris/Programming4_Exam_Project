#include "pch.h"
#include "DigDugCharacter.h"
#include "GameObject.h"
#include "Components.h"
#include "SceneManager.h"
#include "GridLevel.h"


DigDugCharacter::DigDugCharacter()
	:m_MoveSpeed{100}
	,m_Digging{false}
	,m_PrevTile{nullptr}
	, m_DeadTimer{0}
	, m_PumpFlySpeed{2000}
{
	m_DigObject = new dae::GameObject();
	m_DigObject->AddComponent(new dae::SpriteComponent("Tiles/DiggingTunnel.png"));
	auto spriteComp = m_DigObject->GetComponent<dae::SpriteComponent>();
	spriteComp->SetScale({ 0.7f,0.5f });
	spriteComp->SetDoRender(false);
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(m_DigObject);

	m_PumpObject = new dae::GameObject();
	m_PumpObject->SetName(L"DigDugPump");
	m_PumpObject->AddComponent(new dae::SpriteComponent("DigDugPumpShoot.png"));
	m_PumpObject->AddComponent(new dae::PhysicsBodyComponent(b2_dynamicBody));
	m_PumpObject->AddComponent(new dae::ColliderComponent(m_PumpObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_PumpObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(4, 16, dae::ShapeSettings(true, 0.5f, 0, 0));
	m_PumpObject->GetComponent<dae::SpriteComponent>()->SetDoRender(false);;

	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(m_PumpObject);
}


DigDugCharacter::~DigDugCharacter()
{

}

void DigDugCharacter::Initialize()
{
	m_pStateMachineComp = m_pOwnerObject->GetComponent<dae::StateMachineComponent>();
	m_pLevel = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1];
	m_PrevTile = m_pLevel->GetTileByPos(m_pOwnerObject->GetTransform()->GetPosition());
}

void DigDugCharacter::Update()
{
	if (m_Digging)
	{
		dae::GridTile* currTile = m_pLevel->GetTileByPos(m_pOwnerObject->GetTransform()->GetPosition());
		if (m_PrevTile != currTile)
		{
			m_pLevel->AddConnection(m_PrevTile, currTile);
			m_PrevTile = currTile;
			m_DigObject->GetComponent<dae::SpriteComponent>()->SetDoRender(false);
		}
		
		m_DigObject->GetTransform()->SetPosition(m_pOwnerObject->GetTransform()->GetPosition());
	}
	else if (m_pStateMachineComp->GetCurrentStateName() == L"Dead")
	{
		m_DeadTimer += dae::GameInfo::deltaTime;
		if (m_DeadTimer > 0.95f)
			m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Gone");
	}
}
void DigDugCharacter::StartDigging()
{
	auto spriteComp = m_DigObject->GetComponent<dae::SpriteComponent>();
	spriteComp->SetDoRender(true);
	spriteComp->SetAngleDegrees(m_pOwnerObject->GetComponent<dae::TransformComponent>()->GetRotationDegrees());
	spriteComp->SetFlipDirection(m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->GetFlipDirection());
	m_Digging = true;
}

void DigDugCharacter::EndDigging()
{
	m_Digging = false;
}

void DigDugCharacter::Pump()
{
	auto spriteComp = m_PumpObject->GetComponent<dae::SpriteComponent>();
	spriteComp->SetDoRender(true);
	auto rot = m_pOwnerObject->GetComponent<dae::TransformComponent>()->GetRotationDegrees();
	auto flipDir = m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->GetFlipDirection();
	spriteComp->SetAngleDegrees(rot);
	spriteComp->SetFlipDirection(flipDir);
	m_PumpObject->GetTransform()->SetPosition(m_pOwnerObject->GetTransform()->GetPosition());
	b2Vec2 force = { 0,0 };

	if (rot == 90 && flipDir == SDL_FLIP_HORIZONTAL)
		force.y = m_PumpFlySpeed;
	else if (rot == -90 && flipDir == SDL_FLIP_HORIZONTAL)
		force.y = -m_PumpFlySpeed;
	else if (rot == 90 && flipDir == SDL_FLIP_NONE)
		force.y = -m_PumpFlySpeed;
	else if (rot == -90 && flipDir == SDL_FLIP_NONE)
		force.y = m_PumpFlySpeed;
	else if (rot == 0 && flipDir == SDL_FLIP_HORIZONTAL)
		force.x = -m_PumpFlySpeed;
	else if (rot == 0 && flipDir == SDL_FLIP_NONE)
		force.x = m_PumpFlySpeed;

	m_PumpObject->GetComponent<dae::PhysicsBodyComponent>()->ApplyLinearImpulse(force, m_pOwnerObject->GetTransform()->GetPosition());
}

void DigDugCharacter::Render() const
{

}

void DigDugCharacter::PostRender() const
{
}

