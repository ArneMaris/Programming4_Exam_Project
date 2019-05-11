#pragma once
#include <map>
#include "GridTile.h"

namespace dae
{
	struct TileSettings
	{
		std::shared_ptr<SDL_Texture> texture;
		bool m_IsWalkable;
		Prefab* spawnThisOnTile;
	};
	class GridLevel
	{
	public:
		GridLevel(const std::wstring& levelsFilePath, int levelNr);
		virtual ~GridLevel();

		void Render();
		void Update();

	private:
		std::string m_Name;
		int m_HorSize;
		int m_VertSize;
		std::vector<int> m_Nrs;
		//std::vector<Tiles> m_Tiles;
		std::map<const int, const TileSettings> m_TilesMap; //this map you link a number from the file to a GridTile class you made

		std::vector<GridTile*> m_pGridTiles;

		void BuildGridLevel();
		void MakeConnections();
	};
}

