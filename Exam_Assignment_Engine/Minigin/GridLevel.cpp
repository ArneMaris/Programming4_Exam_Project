#include "MiniginPCH.h"
#include "GridLevel.h"
#include "ResourceManager.h"
#include "json.hpp"
#include <fstream>
#include <streambuf>


using nlohmann::json;

dae::GridLevel::GridLevel(const std::wstring & levelFilePath, int levelNr)
{
	UNREFERENCED_PARAMETER(levelNr);
	std::wstring fullPath = { ResourceManager::GetInstance().GetResourcesPath() + levelFilePath };
	std::ifstream file(fullPath);
	std::string wholeFileStr((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
	std::stringstream ss{ wholeFileStr };
	int x = 0;
	while (ss >> x)
	{
		m_Nrs.push_back(x);

		if (ss.peek() == ',')
			ss.ignore();
	}
	m_HorSize = m_Nrs[0];
	m_VertSize = m_Nrs[1];
	BuildGridLevel();
	MakeConnections();
}

dae::GridLevel::~GridLevel()
{
}

void dae::GridLevel::BuildGridLevel()
{
	for (size_t i = 2; i < m_Nrs.size() ; i++)
	{
		if (i < m_TilesMap.size())
		{
			auto it = m_TilesMap.at(m_Nrs[i]);
			m_pGridTiles.push_back(new GridTile(it.texture, it.m_IsWalkable, (it.spawnThisOnTile != nullptr ? it.spawnThisOnTile : nullptr)));
		}
	}
}

void dae::GridLevel::MakeConnections()
{

}

void dae::GridLevel::Render()
{
	
}

