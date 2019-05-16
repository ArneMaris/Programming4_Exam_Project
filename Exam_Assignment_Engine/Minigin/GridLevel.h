#pragma once
#include <map>
#include "GridTile.h"

namespace dae
{
	struct TileSettings
	{
		TileSettings(std::shared_ptr<SDL_Texture> tex, bool walkable, Prefab* spawnThis = nullptr, const b2Vec2& texSizeOffset = { 0,0 })
			:texture{tex}
			,isWalkable{walkable}
			,spawnThisOnTile{spawnThis}
			,textureSizeOffset{ texSizeOffset }
		{}

		std::shared_ptr<SDL_Texture> texture;
		bool isWalkable;
		Prefab* spawnThisOnTile;
		//default {0,0}, if > 0 makes the texture bigger than the tile, if < 0 makes the texture smaller 
		b2Vec2 textureSizeOffset;
	};
	class GridLevel final
	{
	public:
		GridLevel(const std::wstring& levelsFilePath, const b2Vec2& offsetFromCenter);
		virtual ~GridLevel();

		void Render();
		void Initialize();

		void AddTile(int id, const TileSettings& tileSettings);

	private:
		std::wstring m_FilePath;
		int m_HorTiles;
		int m_VertTiles;
		int m_Width;
		int m_Height;
		const b2Vec2 m_CenterOffset;
		std::vector<int> m_Nrs;
		//std::vector<Tiles> m_Tiles;
		std::map<const int, const TileSettings> m_TilesMap; //this map you link a number from the file to a GridTile class you made

		std::vector<GridTile*> m_pGridTiles;

		void BuildGridLevel();
		void MakeConnections();
	};
}

