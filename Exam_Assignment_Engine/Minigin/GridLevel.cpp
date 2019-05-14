#include "MiniginPCH.h"
#include "GridLevel.h"
#include "ResourceManager.h"
#include "json.hpp"
#include <fstream>
#include <streambuf>


using nlohmann::json;

dae::GridLevel::GridLevel(const std::wstring & levelFilePath, const b2Vec2& offsetFromCenter)
	:m_CenterOffset{offsetFromCenter}
{
	std::wstring fullPath = { ResourceManager::GetInstance().GetResourcesPath() + levelFilePath };
	m_FilePath = std::move(fullPath);

}

dae::GridLevel::~GridLevel()
{
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
	startPos.x -= tileWidth * (m_HorTiles / 2.0f);
	startPos.y += tileHeight * (m_VertTiles / 2.0f);
	float yStart = startPos.y;

	std::shared_ptr<SDL_Texture> pErrorTex = ResourceManager::GetInstance().LoadTexture(L"ErrorTile.png");

	for (int hor = 0; hor < m_HorTiles; hor++)
	{
		for (int vert = 0; vert < m_VertTiles; vert++)
		{
			auto it = m_TilesMap.find(m_Nrs[4 + hor]);
			if (it != m_TilesMap.end())
			{
				m_pGridTiles.push_back(new GridTile(startPos, { float(tileWidth),float(tileHeight) }, it->second.texture, it->second.m_IsWalkable, (it->second.spawnThisOnTile != nullptr ? it->second.spawnThisOnTile : nullptr)));
			}
			else
			{
				m_pGridTiles.push_back(new GridTile(startPos, { float(tileWidth),float(tileHeight) }, pErrorTex, false, nullptr));
			}
			startPos.y -= float(tileHeight);
		}
		startPos.x += float(tileWidth);
		startPos.y = yStart;
	}
}


//creates connections between all IsWalkable tiles!
void dae::GridLevel::MakeConnections()
{

	//make horizontal connections
	for (size_t i = 0; i < m_pGridTiles.size(); i++)
	{
		if (i - 1 >= 0)
		{
			//m_pGridTiles[i-1]
			//CONNECT THESE 2
			//m_pGridTiles[i];

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



