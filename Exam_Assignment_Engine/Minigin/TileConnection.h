#pragma once

namespace dae
{
	class GridTile;
	class TileConnection
	{
	public:
		TileConnection(GridTile* frontTile, GridTile* backTile)
			:m_pFrontTile(frontTile)
			,m_pBackTile(backTile)
		{};

		~TileConnection() = default;

		//---- Cost Functions ---
		void SetGCost(float g) { m_GCost = g; }
		float GetGCost() const { return m_GCost; }
		void SetHCost(float h) { m_HCost = h; }
		float GetHCost() const { return m_HCost; }
		float GetFCost() const { return m_GCost + m_HCost; }
		void ResetCosts() { m_GCost = 0; m_FCost = 0; m_HCost = 0; }

		//--- General Functions ---
		TileConnection* GetHeadConnection() const { return m_pFrontConnection; }
		void SetHeadConnection(TileConnection* pC) { m_pFrontConnection = pC; }

		GridTile* GetFront() const {return m_pFrontTile;};
		GridTile* GetBack() const { return m_pBackTile; };

	private:
		GridTile* m_pFrontTile;
		GridTile* m_pBackTile;

		TileConnection* m_pFrontConnection = nullptr; //Holds the connection that has been used to go to this connection

		float m_GCost = 0.f;
		float m_HCost = 0.f;
		float m_FCost = 0.f;
	};

}
