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
{
	m_DigObject = new dae::GameObject();
	m_DigObject->AddComponent(new dae::SpriteComponent("Tiles/DiggingTunnel.png"));
	m_DigObject->GetComponent<dae::SpriteComponent>()->SetSpriteOffset({ 0,0 });
	m_DigObject->GetComponent<dae::SpriteComponent>()->SetScale({ 0.7f,0.5f });
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(m_DigObject);
}


DigDugCharacter::~DigDugCharacter()
{

}

void DigDugCharacter::Initialize()
{
	//m_pStateMachineComp = m_pOwnerObject->GetComponent<dae::StateMachineComponent>();
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

void DigDugCharacter::Render() const
{

}

void DigDugCharacter::PostRender() const
{
}

