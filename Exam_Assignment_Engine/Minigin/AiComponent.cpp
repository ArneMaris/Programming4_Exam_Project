#include "MiniginPCH.h"
#include "AiComponent.h"
#include "TileConnection.h"
#include "GameObject.h"
#include "GridLevel.h"
#include "GridTile.h"
#include <future>
#include <chrono>


dae::AiComponent::AiComponent(float speed, GridLevel* pathfindingLevel, const std::wstring& targetName, long long millisecondsDelay, PathfindingAlgorithm algorithm, Heuristic heuristic)
	:m_CurrentHeuristic{heuristic}
	,m_CurrentPathfinding{algorithm}
	,m_CurrentPathProgress{0}
	,m_Speed{speed}
	,m_DelayMilliseconds{ millisecondsDelay }
	,m_pLevel{ pathfindingLevel }
	,m_pTargetObj{nullptr}
	,m_TargetName{targetName}
	,m_CurrPath{std::vector<b2Vec2>()}
	,m_Active{false}
	,m_CanReachGoal{false}
	, m_TargetPos{0,0}
{
}

dae::AiComponent::~AiComponent()
{
	m_Thread.join();
}

void dae::AiComponent::ThreadLoop()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	m_Active = true;
	while (!GameInfo::gameEnded && !m_pGameObject->GetDeleteMark() && m_pScene->GetIsActive())
	{
		m_TargetPos = (m_pTargetObj->GetTransform()->GetPosition());
		dae::GridTile* targetTile = m_pLevel->GetTileByPos(m_TargetPos);
		dae::GridTile* startTile = m_pLevel->GetTileByPos(m_pTransformComp->GetPosition());

		long long delay = 0;
		if (targetTile != nullptr && startTile != nullptr && startTile->GetConnections().empty() == false)
		{
			std::future<std::vector<b2Vec2>> newPath = std::async(std::launch::async, &AiComponent::CalculateAStar, this, startTile, targetTile);

			std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
			//wait for the newPath, update it, run loop again
			m_CurrentPathProgress = 0;
			newPath.wait();
			m_CurrPath = newPath.get();
			m_CurrentPathProgress = 0;

			auto end = std::chrono::system_clock::now();
			auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			delay = m_DelayMilliseconds - diff;
		}
		else
		{
			delay = m_DelayMilliseconds;
		}
		if (delay > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
}

void dae::AiComponent::Initialize()
{
	m_pTransformComp = m_pGameObject->GetTransform();
	m_pTargetObj = GetObjByNameActiveScene(m_TargetName);
	m_Thread = std::thread(&AiComponent::ThreadLoop, this);
}

void dae::AiComponent::SetActive(bool value)
{
	m_Active = value;
	if (!m_Active)
		m_pGameObject->GetComponent<TransformComponent>()->CancelMoveToPos(0);
}

void dae::AiComponent::Update()
{
	if (!m_Active || m_CurrPath.empty()) return;

	if (b2Distance(m_CurrPath.back(), m_TargetPos) < m_pLevel->GetTileHeight() * 2)
		m_CanReachGoal = true;
	else
		m_CanReachGoal = false;

	if (m_CurrentPathProgress < m_CurrPath.size())
	{
		if (m_pLevel->GetTileByPos(m_CurrPath[m_CurrentPathProgress]) == m_pLevel->GetTileByPos(m_pTransformComp->GetMoveToPosition(), false))
			++m_CurrentPathProgress;

		if (m_CurrentPathProgress < m_CurrPath.size())
			if (m_pTransformComp->MoveToPosition(m_CurrPath[m_CurrentPathProgress], m_Speed))
				++m_CurrentPathProgress;
	}
}


void dae::AiComponent::Render() const
{

}


/*=============================================================================*/
// Copyright 2017-2018 Elite Engine
// Authors: Matthieu Delaere
/*=============================================================================*/
//From from Gameplay programming 2019 used
void dae::AiComponent::CalculateCosts(TileConnection* pC, dae::GridTile* pStartTile, dae::GridTile* pGoalTile)
{
	//Calculate the g and h cost (f is calculate when requested)
	//g = current.g + cost(displacement vector current to this)
	float currentGCost = 0;
	if (pC->GetHeadConnection() != nullptr)
		currentGCost = pC->GetHeadConnection()->GetGCost();

	b2Vec2 parentPos = pStartTile->GetPos();
	if (pC->GetHeadConnection() != nullptr)
		parentPos = pC->GetHeadConnection()->GetFront()->GetPos();

	b2Vec2 tempV = b2Abs(pC->GetBack()->GetPos() - parentPos);
	float gCost = m_CurrentHeuristic(tempV.x, tempV.y);
	pC->SetGCost(currentGCost + gCost);

	//h = distance from absolute displacement vector from this to goal, using the 'heuristicFunction'
	tempV = b2Abs(pC->GetBack()->GetPos() - pGoalTile->GetPos());
	float hCost = m_CurrentHeuristic(tempV.x, tempV.y);
	pC->SetHCost(hCost);
}

//Algorithm from Gameplay programming 2019 used
std::vector<b2Vec2> dae::AiComponent::CalculateAStar(dae::GridTile* pStartTile, dae::GridTile* pGoalTile)
{
	//Variables
	std::vector<b2Vec2> vPath;

	//Temp containers
	std::vector<TileConnection*> openList;
	std::vector<TileConnection*> closedList;
	//Temp variables
	TileConnection* pCurrentConnection = nullptr;

	//TODO: STEP 1 - Start by calculating costs for first possible connections of the 'pStartNode' and adding them to the 'openList'. 
	//This will kick-start the loop!
	for (auto c : pStartTile->GetConnections())
	{
		//*** INSERT CODE ***
		CalculateCosts(c, pStartTile, pGoalTile);
		openList.push_back(c);
	}

	//Start algorithm loop: while our open list is not empty
	while (!openList.empty())
	{
		//TODO: STEP 2.1 - Get the connection with the lowest F score from the 'openList' and set it as 'pCurrentConnection'
		float lowestScore = 999999999.0f;
		for (auto c : openList)
		{
			if (c->GetFCost() < lowestScore)
			{
				lowestScore = c->GetFCost();
				pCurrentConnection = c;
			}
		}

		//TODO: STEP 2.2 - Pop 'pCurrentConnection' off the 'openList' and push it to the 'closedList'
		//Hint:use the "remove-erase idiom"
		closedList.push_back(pCurrentConnection);
		openList.erase(std::remove(openList.begin(), openList.end(), pCurrentConnection), openList.end());

		//TODO: STEP 2.3 - Retrieve the 'connections' for the 'pCurrentConnection's 'EndNode'. 
		//We will use these to check if the goal is present and/or if the need to be added to the openlist later.
		std::vector<TileConnection*> vpConnections = pCurrentConnection->GetBack()->GetConnections();
		if (vpConnections.empty()) return vPath;

		//TODO: STEP 2.4 - If any of the retrieved successors ('vpConnections') is the goal (== connection.'EndNode' == 'pEndNode'), call it a day! 
		//Hint: use std::find_if!
		std::vector<TileConnection*>::iterator result{};
		result = std::find_if(vpConnections.begin(), vpConnections.end(), [&pGoalTile](const TileConnection* c) { return c->GetBack() == pGoalTile; });

		//If something has been found:
		if (result != vpConnections.end())
		{
			//Set the 'HeadConnection' of this found connection ('result') equal to the 'pCurrentConnection'.
			(*result)->SetHeadConnection(pCurrentConnection);
			//Set this connection ('result') as 'pCurrentConnection' (so we can retrace the path).
			pCurrentConnection = (*result);
			//Break the loop by clearing open and breaking!
			break;
		}

		//TODO: STEP 2.5 - Else go over all the retrieved connections
		for (auto pC : vpConnections)
		{
			//2.5.1: If found in 'closedList', do nothing
			//2.5.2: Else:
				//Link the connection by setting the connections its 'HeadConnection' equal to the 'pCurrentConnection' (retrace path).
				//Calculate the costs
				//Add it to the 'openList'
			if (std::find(closedList.begin(), closedList.end(), pC) == closedList.end() && std::find(openList.begin(), openList.end(), pC) == openList.end()) //triggers when not found in closedList
			{
				pC->SetHeadConnection(pCurrentConnection);
				CalculateCosts(pC, pStartTile, pGoalTile);
				openList.push_back(pC);
			}
		}
	}

	//TODO: STEP 3 - Reconstruct path
	//As long as the 'pCurrentConnection' its 'StartNode' is not equal to the 'pStartNode'
		//Store the 'pCurrentConnection' its 'EndNode' position in the 'vPath' container
		//Change the 'pCurrentConnection' to the 'pCurrentConnection' its 'HeadConnection'
	//To finalize add last retrieved 'EndNode' position and the position of 'pStartNode'
	int maxCount = int(m_pLevel->GetAmountOfTiles() * 3);
	int count = 0;
	while (pCurrentConnection->GetFront() != pStartTile)
	{
		if (count > maxCount) break;
		vPath.push_back(pCurrentConnection->GetBack()->GetPos());
		pCurrentConnection = pCurrentConnection->GetHeadConnection();
		count++;
	}
	vPath.push_back(pCurrentConnection->GetBack()->GetPos());
	vPath.push_back(pStartTile->GetPos());

	//Reverse 'vPath' to go from start to goal
	std::reverse(vPath.begin(), vPath.end());

	openList.clear();
	closedList.clear();
	pCurrentConnection = nullptr;

	return vPath;
}


