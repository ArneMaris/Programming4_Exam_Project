#include "pch.h"
#include "DigDugCharacter.h"
#include "GameObject.h"
#include "Components.h"
#include "SceneManager.h"


DigDugCharacter::DigDugCharacter()
	:m_MoveSpeed{100}
{
	m_DigObject = new dae::GameObject();
	m_DigObject->AddComponent(new dae::SpriteComponent("Tiles/DiggingTunnel.png"));
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(m_DigObject);
}


DigDugCharacter::~DigDugCharacter()
{
}

void DigDugCharacter::Initialize()
{
	//m_pStateMachineComp = m_pOwnerObject->GetComponent<dae::StateMachineComponent>();
}

void DigDugCharacter::Update()
{
	if (m_Digging)
	{
	}
}
void DigDugCharacter::StartDigging()
{
	m_DigObject->GetComponent<dae::SpriteComponent>()->SetDoRender(true);
	m_Digging = true;
}

void DigDugCharacter::EndDigging()
{
	m_Digging = false;
	m_DigObject->GetComponent<dae::SpriteComponent>()->SetDoRender(false);
}

void DigDugCharacter::Render() const
{

}

void DigDugCharacter::PostRender() const
{
}

