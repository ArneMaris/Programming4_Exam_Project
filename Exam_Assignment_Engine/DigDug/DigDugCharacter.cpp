#include "pch.h"
#include "DigDugCharacter.h"
#include "GameObject.h"
#include "Components.h"
#include "SceneManager.h"
#include "GridLevel.h"
#include "MenuAndHud.h"
#include "CollisionResponses.h"


DigDugCharacter::DigDugCharacter(bool playerOne)
	:m_MoveSpeed{65}
	,m_Digging{false}
	,m_PrevTile{nullptr}
	, m_DeadTimer{0}
	, m_PumpFlySpeed{2500}
	, m_PumpingSpeed{1} //per sec how many stages (1 stage per sec (when holding))
	, m_PumpCooldown{0}
	, m_PumpFlyDuration{0.4f}
	, m_PumpFlyTimer{0}
	,m_IsPlayerOne{ playerOne }
{
	m_DigObject = new dae::GameObject();
	m_DigObject->AddComponent(new dae::SpriteComponent("Tiles/DiggingTunnel.png"));
	auto spriteComp = m_DigObject->GetComponent<dae::SpriteComponent>();
	spriteComp->SetScale({ 0.7f,0.5f });
	spriteComp->SetDoRender(false);
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(m_DigObject);

	m_PumpObject = new dae::GameObject();
	m_PumpObject->SetName(L"DigDugPump");
	m_PumpObject->SetLayer(2);
	m_PumpObject->AddComponent(new dae::SpriteComponent("DigDugPumpShoot.png"));
	m_PumpObject->AddComponent(new dae::PhysicsBodyComponent(b2_dynamicBody));
	m_PumpObject->AddComponent(new dae::ColliderComponent(m_PumpObject->GetComponent<dae::PhysicsBodyComponent>()));
	m_PumpObject->GetComponent<dae::ColliderComponent>()->AddBoxShape(10, 10, dae::ShapeSettings(true, 0.1f, 0, 0));
	m_PumpObject->GetComponent<dae::ColliderComponent>()->AddCollisionResponse(new PumpCollision());
	m_PumpObject->GetComponent<dae::SpriteComponent>()->SetDoRender(false);
	m_PumpObject->GetComponent<dae::SpriteComponent>()->SetSpriteOffset({ 0,5 });

	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(m_PumpObject);
}

void DigDugCharacter::Initialize()
{
	m_StartPos = m_pOwnerObject->GetTransform()->GetPosition();
	m_pStateMachineComp = m_pOwnerObject->GetComponent<dae::StateMachineComponent>();
	m_pLevel = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1];

}

void DigDugCharacter::Update()
{
	if (m_Pumping)
	{
		m_PumpObject->GetComponent<dae::PhysicsBodyComponent>()->ApplyLinearImpulse(m_PumpForce, m_PumpObject->GetTransform()->GetPosition());

		if (m_pLevel->GetTileByPos(m_PumpObject->GetTransform()->GetPosition())->GetIsWalkable() == false)
			m_PumpFlyTimer = -1;

		m_PumpFlyTimer -= dae::GameInfo::deltaTime;
		if (m_PumpFlyTimer <= 0)
		{
			m_PumpObject->GetComponent<dae::ColliderComponent>()->SetActive(false);
			m_PumpObject->GetComponent<dae::SpriteComponent>()->SetDoRender(false);
			m_Pumping = false;
		}
	}
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
		m_PrevTile = nullptr;
		m_DeadTimer += dae::GameInfo::deltaTime;
		if (m_DeadTimer > 0.96f)
		{
			m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Gone");
			static_cast<MenuAndHud*>(dae::GetObjByNameGlobalScene(L"MenuHud")->GetComponent<dae::ScriptComponent>()->GetScript())->RemoveLife(m_IsPlayerOne);
			m_DeadTimer = -99999;
			m_pOwnerObject->MarkForDelete();
		}

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
	m_DigObject->GetComponent<dae::SpriteComponent>()->SetDoRender(false);
}

void DigDugCharacter::Pump(bool fromHold)
{
	if (fromHold && m_PumpFlyTimer > 0) return;
	if (!fromHold && m_PumpObject->GetComponent<dae::ColliderComponent>()->GetIsActive()) return;

	auto spriteComp = m_PumpObject->GetComponent<dae::SpriteComponent>();
	spriteComp->SetDoRender(true);
	auto rot = m_pOwnerObject->GetComponent<dae::TransformComponent>()->GetRotationDegrees();
	auto flipDir = m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->GetFlipDirection();
	spriteComp->SetAngleDegrees(rot);
	spriteComp->SetFlipDirection(flipDir);
	m_PumpObject->GetTransform()->SetPosition(m_pOwnerObject->GetTransform()->GetPosition());
	m_PumpForce = { 0,0 };

	if (rot == 90 && flipDir == SDL_FLIP_HORIZONTAL)
		m_PumpForce.y = m_PumpFlySpeed;
	else if (rot == -90 && flipDir == SDL_FLIP_HORIZONTAL)
		m_PumpForce.y = -m_PumpFlySpeed;
	else if (rot == 90 && flipDir == SDL_FLIP_NONE)
		m_PumpForce.y = -m_PumpFlySpeed;
	else if (rot == -90 && flipDir == SDL_FLIP_NONE)
		m_PumpForce.y = m_PumpFlySpeed;
	else if (rot == 0 && flipDir == SDL_FLIP_HORIZONTAL)
		m_PumpForce.x = -m_PumpFlySpeed;
	else if (rot == 0 && flipDir == SDL_FLIP_NONE)
		m_PumpForce.x = m_PumpFlySpeed;

	m_Pumping = true;
 	m_PumpObject->GetComponent<dae::ColliderComponent>()->SetActive(true);
	m_PumpFlyTimer = m_PumpFlyDuration;
}

void DigDugCharacter::Render() const
{

}

void DigDugCharacter::PostRender() const
{
}

