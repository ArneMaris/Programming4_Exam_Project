#include "pch.h"
#include "StoneScript.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Components.h"
#include "GridLevel.h"
#include "MenuAndHud.h"

StoneScript::StoneScript()
	: m_Losening{false}
	, m_IsFalling{false}
	, m_TileUnder{nullptr}
	, m_LosenDuration{1}
	, m_LosenTimer{0}
	, m_FallingSpeed{80}
	, m_ScoreGiven{false}
	,m_pDigDug1{nullptr}
	,m_pDigDug2{nullptr}
{
}

void StoneScript::Initialize()
{
	m_Level = dae::SceneManager::GetInstance().GetActiveScene()->GetLevels()[1];
	auto pos = m_pOwnerObject->GetTransform()->GetPosition();
	pos.y -= float(m_Level->GetTileHeight());

	m_TileUnder = m_Level->GetTileByPos(pos);
	m_pDigDug1 = dae::GetObjByNameActiveScene(L"DigDug");
	m_pDigDug2 = dae::GetObjByNameActiveScene(L"DigDug2");
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
			if (!m_ScoreGiven)
			{
				m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Break");
				m_pOwnerObject->SetLifeTime(0.38f);
				int score = 0;
				switch (m_EnemiesHit)
				{
				case 1:
					score = 1000;
					break;
				case 2:
					score = 2500;
					break;
				case 3:
					score = 4000;
					break;
				case 4:
					score = 6000;
					break;
				case 5:
					score = 8000;
					break;
				case 6:
					score = 10000;
					break;
				case 7:
					score = 12000;
					break;
				case 8:
					score = 15000;
					break;
				}
				static_cast<MenuAndHud*>(dae::GetObjByNameGlobalScene(L"MenuHud")->GetComponent<dae::ScriptComponent>()->GetScript())->AddScore(score);
				m_ScoreGiven = true;
			}
		}
		else
		{
			m_pOwnerObject->GetTransform()->MoveToPosition(tileUnder->GetPos(), m_FallingSpeed, true, true, true);
		}
	}
	if (m_TileUnder->GetIsWalkable() && !m_IsFalling)
	{
		bool m_DigDugUnder = false;
		if (m_pDigDug2 != nullptr)
			if (m_TileUnder == m_Level->GetTileByPos(m_pDigDug2->GetTransform()->GetPosition()))
				m_DigDugUnder = true;
		if (m_TileUnder == m_Level->GetTileByPos(m_pDigDug1->GetTransform()->GetPosition()))
			m_DigDugUnder = true;

		if (!m_DigDugUnder)
		{
			m_pOwnerObject->GetComponent<dae::AnimatedSpriteComponent>()->PlayAnimation(L"Losen");
			m_Losening = true;
		}
	}
}

void StoneScript::Render() const
{
}

void StoneScript::PostRender() const
{
}

