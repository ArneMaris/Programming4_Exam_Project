#include "MiniginPCH.h"
#include "GridLevel.h"
#include "ResourceManager.h"
#include "json.hpp"
#include <fstream>
#include <streambuf>


using nlohmann::json;

dae::GridLevel::GridLevel(const std::wstring& levelFilePath, bool usePathfinding, const b2Vec2& offsetFromCenter)
	:m_CenterOffset{offsetFromCenter}
	, m_UsePathfinding{usePathfinding}
{
	std::wstring fullPath = { ResourceManager::GetInstance().GetResourcesPath() + levelFilePath };
	m_FilePath = std::move(fullPath);

}

dae::GridLevel::~GridLevel()
{
	for (auto it = m_pGridTiles.begin(); it != m_pGridTiles.end(); ++it)
	{
		delete (*it);
	}
	m_pGridTiles.clear();
}

void dae::GridLevel::EnablePathfinding()
{
	if (!m_UsePathfinding)
	{
		m_UsePathfinding = true;
		MakeConnections();
	}
}
void dae::GridLevel::Initialize()
{
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
		Logger::GetInstance().LogError(L"Something wrong with level file: " + m_FilePath);
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
		MakeConnections();
}

void dae::GridLevel::AddTile(int id, const TileSettings & tileSettings)
{
	m_TilesMap.insert(std::make_pair(id, tileSettings));
}

void dae::GridLevel::BuildGridLevel()
{
	int tileWidth = m_Width / m_HorTiles;
	int tileHeight = m_Height / m_VertTiles;
	b2Vec2 startPos = b2Vec2{ float(GameInfo::GetInstance().windowWidth / 2),float(GameInfo::GetInstance().windowHeight / 2) } + m_CenterOffset;

	//START IN UPPER LEFT CORNOR BUILD LEVEL FROM LEFT TO RIGHT (BY COLUMN)
	startPos.x -= tileWidth * ((m_HorTiles-1) / 2.0f);
	startPos.y += tileHeight * ((m_VertTiles-1) / 2.0f);
	float xStart = startPos.x;

	std::shared_ptr<SDL_Texture> pErrorTex = ResourceManager::GetInstance().LoadTexture(L"ErrorTile.png");

	for (int vert = 0; vert < m_VertTiles; vert++)
	{
		for (int hor = 0; hor < m_HorTiles; hor++)
		{
			auto it = m_TilesMap.find(m_Nrs[hor + m_HorTiles * vert]);
			if (it != m_TilesMap.end())
			{
				m_pGridTiles.push_back(new GridTile({ startPos.x - it->second.textureSizeOffset.x,startPos.y + it->second.textureSizeOffset.x }, 
					{ float(tileWidth + it->second.textureSizeOffset.x*2),float(tileHeight + it->second.textureSizeOffset.y*2) },
					it->second.texture, it->second.isWalkable, (it->second.spawnThisOnTile != nullptr ? it->second.spawnThisOnTile : nullptr)));
			}
			else
			{
				m_pGridTiles.push_back(new GridTile(startPos, { float(tileWidth),float(tileHeight) }, pErrorTex, true, nullptr));
			}
			startPos.x += float(tileWidth);
		}
		startPos.y -= float(tileHeight);
		startPos.x = xStart;
	}
}


//creates connections between all IsWalkable tiles! (no diagonal connections for now!)
void dae::GridLevel::MakeConnections()
{
	unsigned int index = 0;
	for (int i = 0; i < m_HorTiles; i++)
	{
		for (int j = 0; j < m_VertTiles; j++)
		{
			index = i + j * m_HorTiles;
			//when this tile is not walkable continue
			if (!m_pGridTiles[index]->GetIsWalkable()) continue;

			if (index+1 < m_pGridTiles.size())//1 right
				if (m_pGridTiles[index + 1]->GetIsWalkable())
					m_pGridTiles[index]->AddConnection(m_pGridTiles[index+1]);

			if (index-1 > -1)//1 left
				if (m_pGridTiles[index - 1]->GetIsWalkable())
					m_pGridTiles[index]->AddConnection(m_pGridTiles[index-1]);

			if (index - m_HorTiles > -1)//1 up
				if (m_pGridTiles[index - m_HorTiles]->GetIsWalkable())
					m_pGridTiles[index]->AddConnection(m_pGridTiles[index - m_HorTiles]);

			if (index + m_HorTiles < m_pGridTiles.size())//1 down
				if (m_pGridTiles[index + m_HorTiles]->GetIsWalkable())
					m_pGridTiles[index]->AddConnection(m_pGridTiles[index + m_HorTiles]);
		}
	}
}

void dae::GridLevel::Render()
{
	for (auto& tile : m_pGridTiles)
	{
		tile->Render();
	}
}



