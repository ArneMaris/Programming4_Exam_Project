#pragma once

namespace dae
{
	class GridTile;
	class TileConnection
	{
	public:
		TileConnection(GridTile* frontTile, GridTile* backTile);
		~TileConnection() = default;

	private:
		GridTile* m_pFrontTile;
		GridTile* m_pBackTile;
	};

}
