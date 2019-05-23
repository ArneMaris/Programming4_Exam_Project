#include "pch.h"
#include "StoneScript.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Components.h"
#include "GridLevel.h"

StoneScript::StoneScript()
	: m_Losening{false}
	, m_IsFalling{false}
	, m_TileUnder{nullptr}
	, m_LosenDuration{1}
	, m_LosenTimer{0}
	, m_FallingSpeed{60}
{
}

void StoneScript::Initialize()
{
	m_Level = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1];
	auto pos = m_pOwnerObject->GetTransform()->GetPosition();
	pos.y -= float(m_Level->GetTileHeight());

	m_TileUnder = m_Level->GetTileByPos(pos);
}

void StoneScript::Update()
{
	if (m_pOwnerObject->GetDeleteMark()) return;

	if (m_Losening)
	{
		m_LosenTimer += dae::GameInfo::deltaTime;
		if (m_LosenTimer > m_LosenDuration)
		{
			m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Falling");
			m_IsFalling = true;
			m_Losening = false;
		}
	}
	else if (m_IsFalling)
	{
		auto pos = m_pOwnerObject->GetTransform()->GetPosition();
		auto tile = m_Level->GetTileByPos(pos);
		pos.y -= float(m_Level->GetTileHeight());
		auto tileUnder = m_Level->GetTileByPos(pos);
		//tile under must be walkable and there must be a connection between currentTile and tileUnder (there could be this smaller layer of dirt in between)
		if (tileUnder == m_TileUnder)
		{
			m_pOwnerObject->GetTransform()->MoveToPosition(tileUnder->GetPos(), m_FallingSpeed, true);
			return;
		}

		if (tileUnder->GetIsWalkable() == false || tile->HasConnectionToTile(tileUnder) == false)
		{
			m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Break");
			m_pOwnerObject->SetLifeTime(0.38f);
		}
		else
		{
			m_pOwnerObject->GetTransform()->MoveToPosition(tileUnder->GetPos(), m_FallingSpeed, true, true, true);
		}
	}
	if (m_TileUnder->GetIsWalkable() && !m_IsFalling)
	{
		m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Losen");
		m_Losening = true;
	}
}

void StoneScript::Render() const
{
}

void StoneScript::PostRender() const
{
}

