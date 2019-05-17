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

	//Tile by amount of connections usefull in some cases...
	struct TileByNrConnections
	{
		int NoConnectionTileID = 0;
		int OneConnectionTileID = 0;
		int TwoConnectionsTileID = 0;
		int ThreeConnectionsTileID = 0;
		int FourConnectionsTileID = 0;
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
		GridLevel(const std::wstring& levelFilePath, bool usePathfinding, const TileByNrConnections& tileNrByCon, const b2Vec2& offsetFromCenter = { 0,0 });
		GridLevel(const std::wstring& levelFilePath, bool usePathfinding, const TileRotationsByConnections& tileRotByCon, const b2Vec2& offsetFromCenter = { 0,0 });
		GridLevel(const std::wstring& levelFilePath, bool usePathfinding, const TileRotationsByConnections& tileRotByCon, const TileByNrConnections& tileNrByCon, const b2Vec2& offsetFromCenter = { 0,0 });
		virtual ~GridLevel();

		void Render();
		void Initialize();
		void EnablePathfinding();

		void AddTileConfiguration(int id, const TileSettings& tileSettings);

		void AddConnection(GridTile* fromTile, GridTile* toTile);
		//Does a GetTileByPos to determine the from and toTile for the connection, slower!
		void AddConnection(const b2Vec2& fromPos, const b2Vec2& toPos);

		GridTile* GetTileByPos(const b2Vec2& pos);

	private:
		std::wstring m_FilePath;
		int m_HorTiles;
		int m_VertTiles;
		int m_Width;
		int m_Height;
		const b2Vec2 m_CenterOffset;
		bool m_UsePathfinding;
		bool m_RotateTilesByConnections;
		bool m_SetTileByNrConnections;
		bool m_Initialized;
		std::vector<int> m_Nrs;
		//std::vector<Tiles> m_Tiles;
		std::map<const int, const TileSettings> m_TilesMap; //this map you link a number from the file to a GridTile class you made

		std::vector<GridTile*> m_pGridTiles;

		const TileRotationsByConnections m_TileRotationByConnections;
		const TileByNrConnections m_TileByNrConnections;
		void BuildGridLevel();
		void MakeConnections(bool clearFirst);
		void RotateTilesByConnections();
		void SetTilesByConnections();
	};
}

