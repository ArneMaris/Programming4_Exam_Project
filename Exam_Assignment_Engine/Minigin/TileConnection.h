#pragma once

namespace dae
{
	class GridTile;
	class TileConnection
	{
	public:
		TileConnection(GridTile* frontTile, GridTile* backTile)
			:m_pFrontTile(frontTile)
			, m_pBackTile(backTile)
		{};

		~TileConnection() = default;

		GridTile* GetFront() const {return m_pFrontTile;};
		GridTile* GetBack() const { return m_pBackTile; };

	private:
		GridTile* m_pFrontTile;
		GridTile* m_pBackTile;
	};

}
