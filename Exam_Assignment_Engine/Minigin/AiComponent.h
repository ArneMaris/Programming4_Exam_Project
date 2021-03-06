#pragma once
#include "BaseComponent.h"
#include "GridTile.h"
#include "HeuristicFunctions.h"
#include <thread>
#include <condition_variable>

namespace dae
{
	class AiComponent : public BaseComponent
	{
	public:
		enum PathfindingAlgorithm
		{
			Astar
		};
		AiComponent(float speed,  GridLevel* pathfindingLevel, const std::wstring& targetName, long long millisecondsDelay = 300, PathfindingAlgorithm algorithm = PathfindingAlgorithm::Astar, Heuristic heuristic = Euclidean);
		~AiComponent();

		AiComponent(const AiComponent& other) = delete;
		AiComponent(AiComponent&& other) noexcept = delete;
		AiComponent& operator=(const AiComponent& other) = delete;
		AiComponent& operator=(AiComponent&& other) noexcept = delete;

		void SetHeuristicFunction(Heuristic heuristicFunc) {m_CurrentHeuristic = heuristicFunc;};
		void SetSpeed(float newSpeed) { m_Speed = newSpeed; };
		float GetSpeed() const { return m_Speed; };

		void SetActive(bool value);
		bool IsActive() const { return m_Active; };
		bool GetCanReachGoal() const { return (m_Active == true ? m_CanReachGoal : false); };

		void SetNewTarget(GameObject* newTargetObj);

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;

	private:
		void CalculateCosts(TileConnection* pC, GridTile* pStartTile, GridTile* pGoalTile);
		std::vector<b2Vec2> CalculateAStar(GridTile* pStartTile, GridTile* pGoalTile);
		void ThreadLoop();

		size_t m_CurrentPathProgress;
		std::vector<b2Vec2> m_CurrPath;

		Heuristic m_CurrentHeuristic;
		PathfindingAlgorithm m_CurrentPathfinding;
		TransformComponent* m_pTransformComp;
		GridLevel* m_pLevel;
		GameObject* m_pTargetObj;
		std::wstring m_TargetName;

		Scene* m_pScene;

		b2Vec2 m_TargetPos;

		float m_Speed;
		long long m_DelayMilliseconds;

		std::thread m_Thread;
		bool m_End;

		bool m_Active;
		bool m_CanReachGoal;
	};
}

