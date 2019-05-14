#include "MiniginPCH.h"
#include "TileConnection.h"

dae::TileConnection::TileConnection(GridTile * frontTile, GridTile * backTile)
	:m_pFrontTile(frontTile)
	,m_pBackTile(backTile)
{
}
