#include "pch.h"
#include "InputResponsesPlayerFygar.h"
#include "StateMachineComponent.h"
#include "AnimatedSpriteComponent.h"
#include "GridLevel.h"

void PlayerFygarAttack::ExecuteOnPress()
{
	if (m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->GetCurrentStateName() == L"Run")
		m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"FygarAttack");
}

void PlayerFygarAttack::ExecuteOnRelease()
{

}

void PlayerFygarMove::ExecuteOnPress()
{
}

void PlayerFygarMove::ExecuteOnHold(const b2Vec2 axisValues)
{
	if (dae::SceneManager::GetInstance().GetActiveScene() == nullptr) return;

	auto level = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1];
	b2Vec2 frontPos;
	frontPos = m_pOwnerObject->GetTransform()->GetPosition();
	auto tile = level->GetTileByPos(m_pOwnerObject->GetTransform()->GetPosition());
	if (tile->GetIsWalkable())
	{
		m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->TryTransitionToState(L"Ghost", L"Run");
	}
	else
	{
		m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->TryTransitionToState(L"Run", L"Ghost");
	}

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

		if (angle > 0)
			m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetFlipDirection(SDL_FLIP_NONE);
		else
			m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->SetFlipDirection(SDL_FLIP_HORIZONTAL);
	}
	else
	{
		frontPos.y += float(level->GetTileHeight());
	}

	tile = level->GetTileByPos(frontPos);
	m_pOwnerObject->GetTransform()->MoveToPosition(tile->GetPos(), 30, true);
}

void PlayerFygarMove::ExecuteOnRelease()
{
	auto tile = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1]->GetTileByPos(m_pOwnerObject->GetTransform()->GetPosition());
	if (tile->GetIsWalkable())
	{
		m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->TryTransitionToState(L"Ghost", L"Run");
	}
	else
	{
		m_pOwnerObject->GetComponent<dae::StateMachineComponent>()->TryTransitionToState(L"Run", L"Ghost");
	}
}
