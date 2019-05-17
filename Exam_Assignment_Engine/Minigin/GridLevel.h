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
	//rotation based on connections, usefull for: tunnels, roads, etc
	struct TileRotationsByConnections
	{
		bool OnlyRotateWalkable = true;
		int None = 0;
		int Up = 0;
		int Down = 0;
		int Left = 0;
		int Right = 0;
		int UpLeft = 0;
		int UpRight = 0;
		int DownLeft = 0;
		int DownRight = 0;
		int UpDown = 0;
		int LeftRight = 0;
		int UpDownLeft = 0;
		int UpDownRight = 0;
		int LeftRightUp = 0;
		int LeftRightDown = 0;
		int UpDownLeftRight = 0;
	};
	class GridLevel final
	{
	public:
		GridLevel(const std::wstring& levelFilePath, bool usePathfinding, const b2Vec2& offsetFromCenter = { 0,0 });
		virtual ~GridLevel();

		void Render();
		void Initialize();
		void EnablePathfinding();

		void AddTile(int id, const TileSettings& tileSettings);

	private:
		std::wstring m_FilePath;
		int m_HorTiles;
		int m_VertTiles;
		int m_Width;
		int m_Height;
		const b2Vec2 m_CenterOffset;
		bool m_UsePathfinding;
		std::vector<int> m_Nrs;
		//std::vector<Tiles> m_Tiles;
		std::map<const int, const TileSettings> m_TilesMap; //this map you link a number from the file to a GridTile class you made

		std::vector<GridTile*> m_pGridTiles;

		void BuildGridLevel();
		void MakeConnections();
	};
}

