#include "pch.h"
#include "InputResponses.h"
#include "GameObject.h"
#include "Components.h"
#include "DigDugCharacter.h"
#include "SceneManager.h"
#include "GridLevel.h"

void MoveController::ExecuteOnPress()
{
}

void MoveController::ExecuteOnHold(const b2Vec2 axisValues)
{
	b2Vec2 frontPos;
	frontPos = m_pOwnerObject->GetTransform()->GetPosition();
	auto level = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1];
	float moveSpeed = static_cast<DigDugCharacter*>(m_pOwnerObject->GetComponent<dae::ScriptComponent>()->GetScript())->GetMoveSpeed();

	float angle = RadToDegrees(atan2f(axisValues.x, axisValues.y));
	if (abs(angle) > 135)
	{
		frontPos.y -= float(level->GetTileHeight());
	}
	else if (abs(angle) > 45)
	{
		if (angle > 0)
			frontPos.x += float(level->GetTileWidth());
		else
			frontPos.x -= float(level->GetTileWidth());
	}
	else
	{
		frontPos.y += float(level->GetTileHeight());
	}

	auto tile = level->GetTileByPos(frontPos);

	if (!m_pOwnerObject->GetTransform()->MoveToPosition(tile->GetPos(), moveSpeed, true)) return;

	//So only rotate if new moveTarget is set
	if (abs(angle) > 135)
	{
		if (m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->GetFlipDirection() == SDL_FLIP_HORIZONTAL)
			m_pOwnerObject->GetTransform()->SetRotation(-90);
		else
			m_pOwnerObject->GetTransform()->SetRotation(90);
	}
	else if (abs(angle) > 45)
	{
		if (angle > 0)
			m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetFlipDirection(SDL_FLIP_NONE);
		else
			m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetFlipDirection(SDL_FLIP_HORIZONTAL);
		m_pOwnerObject->GetTransform()->SetRotation(0);
	}
	else
	{
		if (m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->GetFlipDirection() == SDL_FLIP_HORIZONTAL)
			m_pOwnerObject->GetTransform()->SetRotation(90);
		else
			m_pOwnerObject->GetTransform()->SetRotation(-90);
	}
}
void MoveController::ExecuteOnRelease()
{
}

void MoveUpKey::ExecuteOnPress()
{

}

void MoveUpKey::ExecuteOnHold(const b2Vec2 axisValues)
{
	UNREFERENCED_PARAMETER(axisValues);
	b2Vec2 frontPos;
	frontPos = m_pOwnerObject->GetTransform()->GetPosition();
	auto level = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1];
	float moveSpeed = static_cast<DigDugCharacter*>(m_pOwnerObject->GetComponent<dae::ScriptComponent>()->GetScript())->GetMoveSpeed();

	frontPos.y += level->GetTileHeight();
	auto tile = level->GetTileByPos(frontPos);

	if (!m_pOwnerObject->GetTransform()->MoveToPosition(tile->GetPos(), moveSpeed, true)) return;

	if (m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->GetFlipDirection() == SDL_FLIP_HORIZONTAL)
		m_pOwnerObject->GetTransform()->SetRotation(90);
	else
		m_pOwnerObject->GetTransform()->SetRotation(-90);
}

void MoveUpKey::ExecuteOnRelease()
{
}

void MoveDownKey::ExecuteOnPress()
{
}

void MoveDownKey::ExecuteOnHold(const b2Vec2 axisValues)
{
	UNREFERENCED_PARAMETER(axisValues);
	b2Vec2 frontPos;
	frontPos = m_pOwnerObject->GetTransform()->GetPosition();
	auto level = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1];
	float moveSpeed = static_cast<DigDugCharacter*>(m_pOwnerObject->GetComponent<dae::ScriptComponent>()->GetScript())->GetMoveSpeed();

	frontPos.y -= level->GetTileHeight();
	auto tile = level->GetTileByPos(frontPos);

	if (!m_pOwnerObject->GetTransform()->MoveToPosition(tile->GetPos(), moveSpeed, true)) return;

	if (m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->GetFlipDirection() == SDL_FLIP_HORIZONTAL)
		m_pOwnerObject->GetTransform()->SetRotation(-90);
	else
		m_pOwnerObject->GetTransform()->SetRotation(90);
}

void MoveDownKey::ExecuteOnRelease()
{
}

void MoveLeftKey::ExecuteOnPress()
{
}

void MoveLeftKey::ExecuteOnHold(const b2Vec2 axisValues)
{
	UNREFERENCED_PARAMETER(axisValues);
	b2Vec2 frontPos;
	frontPos = m_pOwnerObject->GetTransform()->GetPosition();
	auto level = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1];
	float moveSpeed = static_cast<DigDugCharacter*>(m_pOwnerObject->GetComponent<dae::ScriptComponent>()->GetScript())->GetMoveSpeed();

	frontPos.x -= level->GetTileWidth();
	auto tile = level->GetTileByPos(frontPos);

	if (!m_pOwnerObject->GetTransform()->MoveToPosition(tile->GetPos(), moveSpeed, true)) return;

	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetFlipDirection(SDL_FLIP_HORIZONTAL);
	m_pOwnerObject->GetTransform()->SetRotation(0);
}

void MoveLeftKey::ExecuteOnRelease()
{
}

void MoveRightKey::ExecuteOnPress()
{
}

void MoveRightKey::ExecuteOnHold(const b2Vec2 axisValues)
{
	UNREFERENCED_PARAMETER(axisValues);
	b2Vec2 frontPos;
	frontPos = m_pOwnerObject->GetTransform()->GetPosition();
	auto level = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1];
	float moveSpeed = static_cast<DigDugCharacter*>(m_pOwnerObject->GetComponent<dae::ScriptComponent>()->GetScript())->GetMoveSpeed();

	frontPos.x += level->GetTileWidth();
	auto tile = level->GetTileByPos(frontPos);

	if (!m_pOwnerObject->GetTransform()->MoveToPosition(tile->GetPos(), moveSpeed, true)) return;

	m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetFlipDirection(SDL_FLIP_NONE);
	m_pOwnerObject->GetTransform()->SetRotation(0);
}

void MoveRightKey::ExecuteOnRelease()
{
}
