#include "MiniginPCH.h"
#include "GridLevel.h"
#include "ResourceManager.h"
#include <fstream>
#include <streambuf>
#include "TileConnection.h"
#include "Prefab.h"

dae::GridLevel::GridLevel(const std::string& levelFilePath, bool usePathfinding, const b2Vec2& offsetFromCenter)
	:m_CenterOffset{ offsetFromCenter }
	, m_UsePathfinding{ usePathfinding }
	, m_SetTileByNrConnections{ false }
	, m_RotateTilesByConnections{ false }
	, m_TileRotationByConnections{}
	, m_TileByNrConnections{ 0,0,0,0,0,0 }
{
	m_FilePath = std::move(ResourceManager::GetInstance().GetResourcesPath() + levelFilePath);

}

dae::GridLevel::GridLevel(const std::string & levelFilePath, bool usePathfinding, const TileByNrConnections & tileNrByCon, const b2Vec2 & offsetFromCenter)
	:m_CenterOffset{ offsetFromCenter }
	, m_UsePathfinding{ usePathfinding }
	, m_TileByNrConnections{ tileNrByCon }
	, m_TileRotationByConnections{}
	, m_SetTileByNrConnections{ true }
	, m_RotateTilesByConnections{ false }
{
	m_FilePath = std::move(ResourceManager::GetInstance().GetResourcesPath() + levelFilePath);
}

dae::GridLevel::GridLevel(const std::string & levelFilePath, bool usePathfinding, const TileRotationsByConnections & tileRotByCon, const b2Vec2 & offsetFromCenter)
	:m_CenterOffset{ offsetFromCenter }
	, m_UsePathfinding{ usePathfinding }
	, m_TileRotationByConnections{ tileRotByCon }
	, m_TileByNrConnections{ 0,0,0,0,0,0 }
	, m_SetTileByNrConnections{ false }
	, m_RotateTilesByConnections{ true }

{
	m_FilePath = std::move(ResourceManager::GetInstance().GetResourcesPath() + levelFilePath);
}

dae::GridLevel::GridLevel(const std::string & levelFilePath, bool usePathfinding, const TileRotationsByConnections & tileRotByCon, const TileByNrConnections & tileNrByCon, const b2Vec2 & offsetFromCenter)
	:m_CenterOffset{ offsetFromCenter }
	, m_UsePathfinding{ usePathfinding }
	, m_TileRotationByConnections{ tileRotByCon }
	, m_TileByNrConnections{ tileNrByCon }
	, m_SetTileByNrConnections{ true }
	, m_RotateTilesByConnections{ true }
{
	m_FilePath = std::move(ResourceManager::GetInstance().GetResourcesPath() + levelFilePath);
}

dae::GridLevel::~GridLevel()
{
	for (auto it = m_pGridTiles.begin(); it != m_pGridTiles.end(); ++it)
	{
		delete (*it);
	}
	for (auto tileConfig : m_TilesMap)
	{
		delete tileConfig.second.spawnThisOnTile;
	}
	m_pGridTiles.clear();
}

void dae::GridLevel::EnablePathfinding()
{
	if (!m_UsePathfinding)
	{
		m_UsePathfinding = true;
		MakeConnections(true);
	}
}
void dae::GridLevel::Initialize()
{
	if (m_Initialized) return;

	std::ifstream file(m_FilePath);
	std::string wholeFileStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	std::stringstream ss{ wholeFileStr };
	try
	{
		int x = 0;
		while (ss >> x)
		{
			m_Nrs.push_back(x);

			if (ss.peek() == ',')
				ss.ignore();
		}
	}
	catch (std::exception&)
	{
		Logger::GetInstance().LogError(L"Something wrong with level file");
		return;
	}
	m_Width = m_Nrs[0];
	m_Height = m_Nrs[1];
	m_HorTiles = m_Nrs[2];
	m_VertTiles = m_Nrs[3];
	m_Nrs.erase(m_Nrs.begin(), m_Nrs.begin() + 4);
	m_Nrs.shrink_to_fit();
	if (int(m_Nrs.size()) != (m_HorTiles * m_VertTiles))
	{
		Logger::GetInstance().LogError(L"Level file error, grid data not as big as HorSize * VertSize!");
		return;
	}

	BuildGridLevel();

	if (m_UsePathfinding)
		MakeConnections(false);

	if (m_SetTileByNrConnections || m_RotateTilesByConnections)
	{
		BuildDirectionCodesForTiles();
		UpdateTileTextureAndRotation(m_pGridTiles);
	}

	m_Initialized = true;
}

void dae::GridLevel::AddTileConfiguration(unsigned int id, const TileSettings& tileSettings)
{
	m_TilesMap.insert(std::make_pair(id, tileSettings));
}

void dae::GridLevel::AddConnection(GridTile * fromTile, GridTile * toTile)
{
	if (toTile != nullptr && fromTile != nullptr && toTile->m_Id != fromTile->m_Id)
	{
		if (!fromTile->HasConnectionToTile(toTile->m_Id))
			fromTile->AddConnection(toTile);

		if (!toTile->HasConnectionToTile(fromTile->m_Id))
		{
			toTile->AddConnection(fromTile);
			toTile->m_IsWalkable = true;
		}

		if (m_RotateTilesByConnections || m_SetTileByNrConnections)
		{
			std::vector<GridTile*> tiles;
			tiles.reserve(6);
			tiles.push_back(fromTile);
			tiles.push_back(toTile);
			for (auto& con : toTile->m_pConnections)
				tiles.push_back(con->GetBack());

			std::sort(tiles.begin(), tiles.end());
			tiles.erase(std::unique(tiles.begin(), tiles.end()), tiles.end());

			UpdateTileTextureAndRotation(tiles);
		}
	}
}

void dae::GridLevel::AddConnection(const b2Vec2 & fromPos, const b2Vec2 & toPos)
{
	auto fromTile = GetTileByPos(fromPos, false);
	auto toTile = GetTileByPos(toPos, false);
	AddConnection(fromTile, toTile);
}

dae::GridTile* dae::GridLevel::GetTileByPos(const b2Vec2 & pos, bool clip)
{
	//first check hor pos;
	unsigned int columnWidth = m_Width / m_HorTiles;
	unsigned int rowHeight = m_Height / m_VertTiles;
	b2Vec2 diff{ 0,0 };
	diff.x = (float(GameInfo::windowWidth - m_Width) / 2) + m_CenterOffset.x;
	diff.y = (float(GameInfo::windowHeight - m_Height) / 2) + m_CenterOffset.y;
	int row = -1;
	int column = -1;

	for ( int i = 0; i < int(m_HorTiles); i++)
	{
		if (pos.x - diff.x > (i * columnWidth) && pos.x - diff.x < ((i + 1) * columnWidth))
		{
			column = i;
			break;
		}
		else if (clip)
		{
			if (pos.x - diff.x >= (GameInfo::windowWidth / 2) - (m_Width / 2) + m_CenterOffset.x)
				column = m_HorTiles-1;
			else if (pos.x - diff.x <= (GameInfo::windowWidth / 2) + (m_Width / 2) + m_CenterOffset.x)
				column = 0;
		}
	}
	for ( int i = 0; i < int(m_VertTiles); i++)
	{
		if (pos.y - diff.y > (i * rowHeight) && pos.y - diff.y < ((i + 1) * rowHeight))
		{
			//level is made from leftTop to rightBot
			row = m_VertTiles - 1 - i;
			break;
		}
		else if (clip)
		{
			if (pos.y - diff.y >= GameInfo::windowHeight / 2 + m_Height / 2 + m_CenterOffset.y)
				row = 0;
			else if (pos.y - diff.y <= GameInfo::windowHeight / 2 - m_Height / 2 + m_CenterOffset.y)
				row = m_VertTiles-1;
		}
	}
	if (row >= 0 && row < int(m_VertTiles) && column >= 0 && column < int(m_HorTiles))
	{
		return m_pGridTiles[column + row * m_HorTiles];
	}
	else
	{
		if (clip)
		{
			Logger::GetInstance().LogWarning(L"Tile on this position not found! Returned nullptr!");
			return m_pGridTiles[0];
		}

		return nullptr;
	}
}

dae::GridTile * dae::GridLevel::GetWalkableTileInRadius(const b2Vec2 & center, int minTilesDist, int maxTilesDist)
{
	auto startId = GetTileByPos(center)->m_Id;
	//loop makes sure you goe further and further when not finding anything close
	for (int i = minTilesDist; i < maxTilesDist; i++)
	{
		int id = startId;
		int incrementer;
		switch (rand() % 8)
		{
		case 0:
			incrementer = 1;
			break;
		case 1:
			incrementer = -1;
			break;
		case 2:
			incrementer = int(m_HorTiles);
			break;
		case 3:
			incrementer = -int(m_HorTiles);
			break;
		case 4:
			incrementer = int(m_HorTiles) + 1;
			break;
		case 5:
			incrementer = int(m_HorTiles) - 1;
			break;
		case 6:
			incrementer = -int(m_HorTiles) + 1;
			break;
		case 7:
			incrementer = -int(m_HorTiles) - 1;
			break;
		default:
			incrementer = 0;
			break;
		}
		id += incrementer * i;
		if (id >= 0 && id < int(m_pGridTiles.size()))
		{
			if (m_pGridTiles[id]->GetIsWalkable())
			{
				return m_pGridTiles[id];
			}
		}
	}

	Logger::GetInstance().LogWarning(L"No Tile around this center found! Returned nullptr!");
	return nullptr;
}

void dae::GridLevel::BuildGridLevel()
{
	unsigned int tileWidth = m_Width / m_HorTiles;
	unsigned int tileHeight = m_Height / m_VertTiles;
	b2Vec2 startPos = b2Vec2{ float(GameInfo::windowWidth / 2),float(GameInfo::windowHeight / 2) } + m_CenterOffset;

	//START IN UPPER LEFT CORNOR BUILD LEVEL FROM LEFT TO RIGHT (BY COLUMN)
	startPos.x -= tileWidth * ((m_HorTiles - 1) / 2.0f);
	startPos.y += tileHeight * ((m_VertTiles - 1) / 2.0f);
	float xStart = startPos.x;

	auto scene = SceneManager::GetInstance().GetActiveScene();

	std::shared_ptr<SDL_Texture> pErrorTex = ResourceManager::GetInstance().LoadTexture("ErrorTile.png");

	m_pGridTiles.reserve(m_HorTiles * m_VertTiles);

	for (unsigned int row = 0; row < m_VertTiles; row++)
	{
		for (unsigned int column = 0; column < m_HorTiles; column++)
		{
			int index = column + m_HorTiles * row;
			auto it = m_TilesMap.find(m_Nrs[index]);
			if (it != m_TilesMap.end())
			{
				m_pGridTiles.push_back(new GridTile(scene, index, { startPos.x - it->second.textureSizeOffset.x, startPos.y + it->second.textureSizeOffset.x },
					{ float(tileWidth + it->second.textureSizeOffset.x * 2), float(tileHeight + it->second.textureSizeOffset.y * 2) },
					it->second.texture, it->second.isWalkable, it->second.isChangable, it->second.spawnThisOnTile));
			}
			else
			{
				m_pGridTiles.push_back(new GridTile(scene, index, startPos, { float(tileWidth),float(tileHeight) }, pErrorTex, false, false, nullptr));
			}
			startPos.x += float(tileWidth);
		}
		startPos.y -= float(tileHeight);
		startPos.x = xStart;
	}
}

//creates connections between all IsWalkable tiles! (no diagonal connections for now!)
void dae::GridLevel::MakeConnections(bool clearFirst)
{
	if (clearFirst)
	{
		for (auto& tile : m_pGridTiles)
		{
			tile->ClearAllConnections();
		}
	}
	int index = 0;
	for (unsigned int i = 0; i < m_VertTiles; i++)
	{
		for (unsigned int j = 0; j < m_HorTiles; j++)
		{
			index = j + i * m_HorTiles;
			//when this tile is not walkable continue
			if (!m_pGridTiles[index]->m_IsWalkable) continue;

			if (index - 1 > -1)//1 left
				if (m_pGridTiles[index - 1]->m_IsWalkable)
					m_pGridTiles[index]->AddConnection(m_pGridTiles[index - 1]);

			if (index + 1 < int(m_pGridTiles.size()))//1 right
				if (m_pGridTiles[index + 1]->m_IsWalkable)
					m_pGridTiles[index]->AddConnection(m_pGridTiles[index + 1]);

			if (index - int(m_HorTiles) > -1)//1 up
				if (m_pGridTiles[index - m_HorTiles]->m_IsWalkable)
					m_pGridTiles[index]->AddConnection(m_pGridTiles[index - m_HorTiles]);

			if (index + m_HorTiles < int(m_pGridTiles.size()))//1 down
				if (m_pGridTiles[index + m_HorTiles]->m_IsWalkable)
					m_pGridTiles[index]->AddConnection(m_pGridTiles[index + m_HorTiles]);
		}
	}

}

void dae::GridLevel::UpdateTileTextureAndRotation(const std::vector<GridTile*>& gridTilesToChange)
{
	std::pair<unsigned int, unsigned int> values;
	unsigned int code = 0;
	auto it = m_DirectionCodesForTiles.end();
	for (auto& tile : gridTilesToChange)
	{
		if (tile->m_IsChangeable)
		{
			switch (tile->m_pConnections.size())
			{
			case 0:
				tile->m_pTexture = m_TilesMap[m_TileByNrConnections.NoConnectionTileID].texture;
				break;
			case 1:
				if (m_SetTileByNrConnections)
					tile->m_pTexture = m_TilesMap[m_TileByNrConnections.OneConnectionTileID].texture;

				if (m_RotateTilesByConnections)
				{
					switch (GetConnectionDirection(tile->m_Id, tile->m_pConnections[0]->GetBack()->m_Id))
					{
					case ConnectionDirection::left:
						tile->m_Rotation = m_TileRotationByConnections.Left;
						break;
					case ConnectionDirection::right:
						tile->m_Rotation = m_TileRotationByConnections.Right;
						break;
					case ConnectionDirection::up:
						tile->m_Rotation = m_TileRotationByConnections.Up;
						break;
					case ConnectionDirection::down:
						tile->m_Rotation = m_TileRotationByConnections.Down;
						break;
					}
				}
				break;
			case 2:
				code = GetConnectionDirection(tile->m_Id, tile->m_pConnections[0]->GetBack()->m_Id) + GetConnectionDirection(tile->m_Id, tile->m_pConnections[1]->GetBack()->m_Id);
				
				it = m_DirectionCodesForTiles.find(code);
				if (it != m_DirectionCodesForTiles.end())
					values = it->second;
				else
					return;

				if (m_SetTileByNrConnections)
					tile->m_pTexture = m_TilesMap.at(values.first).texture;
				if (m_RotateTilesByConnections)
					tile->m_Rotation = values.second;
				break;
			case 3:
				code = GetConnectionDirection(tile->m_Id, tile->m_pConnections[0]->GetBack()->m_Id)
					+ GetConnectionDirection(tile->m_Id, tile->m_pConnections[1]->GetBack()->m_Id)
					+ GetConnectionDirection(tile->m_Id, tile->m_pConnections[2]->GetBack()->m_Id);

				it = m_DirectionCodesForTiles.find(code);
				if (it != m_DirectionCodesForTiles.end())
					values = it->second;
				else
					return;

				if (m_SetTileByNrConnections)
					tile->m_pTexture = m_TilesMap.at(values.first).texture;
				if (m_RotateTilesByConnections)
					tile->m_Rotation = values.second;
				break;
			case 4:
				tile->m_pTexture = m_TilesMap[m_TileByNrConnections.FourConnectionsTileID].texture;
				break;
			}
		}
	}
}


void dae::GridLevel::BuildDirectionCodesForTiles()
{
	std::pair<unsigned int, std::pair<unsigned int, unsigned int>> valueToInsert;
	m_DirectionCodesForTiles.clear();
	m_DirectionCodesForTiles.reserve(10);

	//allocate this variable 11 times (6 times for 2 connections, 4 times for 3 connections

	//~~~~~~~~~~~~~~~~~~~~~~~~~ 2 CONNECTIONS~~~~~~~~~~~~~~~~~~~~~~~~
	//Up-Left
	valueToInsert.first = ConnectionDirection::up + ConnectionDirection::left;
	valueToInsert.second.first = m_TileByNrConnections.TwoConnectionsCornerTileID;
	valueToInsert.second.second = m_TileRotationByConnections.UpLeft;
	m_DirectionCodesForTiles.insert(valueToInsert);

	//Up-Right
	valueToInsert.first = ConnectionDirection::up + ConnectionDirection::right;
	valueToInsert.second.first = m_TileByNrConnections.TwoConnectionsCornerTileID;
	valueToInsert.second.second = m_TileRotationByConnections.UpRight;
	m_DirectionCodesForTiles.insert(valueToInsert);

	//Down-Left
	valueToInsert.first = ConnectionDirection::down + ConnectionDirection::left;
	valueToInsert.second.first = m_TileByNrConnections.TwoConnectionsCornerTileID;
	valueToInsert.second.second = m_TileRotationByConnections.DownLeft;
	m_DirectionCodesForTiles.insert(valueToInsert);

	//Down-Right
	valueToInsert.first = ConnectionDirection::down + ConnectionDirection::right;
	valueToInsert.second.first = m_TileByNrConnections.TwoConnectionsCornerTileID;
	valueToInsert.second.second = m_TileRotationByConnections.DownRight;
	m_DirectionCodesForTiles.insert(valueToInsert);

	//Left-Right
	valueToInsert.first = ConnectionDirection::left + ConnectionDirection::right;
	valueToInsert.second.first = m_TileByNrConnections.TwoConnectionsStraightTileID;
	valueToInsert.second.second = m_TileRotationByConnections.LeftRight;
	m_DirectionCodesForTiles.insert(valueToInsert);

	//Up-Down
	valueToInsert.first = ConnectionDirection::up + ConnectionDirection::down;
	valueToInsert.second.first = m_TileByNrConnections.TwoConnectionsStraightTileID;
	valueToInsert.second.second = m_TileRotationByConnections.UpDown;
	m_DirectionCodesForTiles.insert(valueToInsert);

	//~~~~~~~~~~~~~~~~~~~~~~~~~ 3 CONNECTIONS~~~~~~~~~~~~~~~~~~~~~~~~
	//Up-Down-Left
	valueToInsert.first = ConnectionDirection::up + ConnectionDirection::down + ConnectionDirection::left;
	valueToInsert.second.first = m_TileByNrConnections.ThreeConnectionsTileID;
	valueToInsert.second.second = m_TileRotationByConnections.UpDownLeft;
	m_DirectionCodesForTiles.insert(valueToInsert);

	//Up-Down-Right
	valueToInsert.first = ConnectionDirection::up + ConnectionDirection::down + ConnectionDirection::right;
	valueToInsert.second.first = m_TileByNrConnections.ThreeConnectionsTileID;
	valueToInsert.second.second = m_TileRotationByConnections.UpDownRight;
	m_DirectionCodesForTiles.insert(valueToInsert);

	//Left-Right-Up
	valueToInsert.first = ConnectionDirection::left + ConnectionDirection::right + ConnectionDirection::up;
	valueToInsert.second.first = m_TileByNrConnections.ThreeConnectionsTileID;
	valueToInsert.second.second = m_TileRotationByConnections.LeftRightUp;
	m_DirectionCodesForTiles.insert(valueToInsert);

	//Left-Right-Down
	valueToInsert.first = ConnectionDirection::left + ConnectionDirection::right + ConnectionDirection::down;
	valueToInsert.second.first = m_TileByNrConnections.ThreeConnectionsTileID;
	valueToInsert.second.second = m_TileRotationByConnections.LeftRightDown;
	m_DirectionCodesForTiles.insert(valueToInsert);
}

dae::GridLevel::ConnectionDirection dae::GridLevel::GetConnectionDirection(unsigned int IdOne, unsigned int IdTwo)
{
	//if true, connection to left
	if (int(IdOne) - 1 == int(IdTwo))
	{
		return ConnectionDirection::left;
	}
	//if true, connection to right
	else if (IdOne + 1 == IdTwo)
	{
		return ConnectionDirection::right;
	}
	//if true, connection to top
	else if ((int(IdOne) - int(m_HorTiles)) == int(IdTwo))
	{
		return ConnectionDirection::up;
	}
	//if true, connection to bot
	else if ((IdOne + m_HorTiles) == IdTwo)
	{
		return ConnectionDirection::down;
	}
	return ConnectionDirection::none;
}


void dae::GridLevel::Render()
{
	for (auto& tile : m_pGridTiles)
	{
		tile->Render();
	}
}



