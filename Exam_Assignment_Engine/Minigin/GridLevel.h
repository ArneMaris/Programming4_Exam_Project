#pragma once
#include <unordered_map>
#include <map>
#include "GridTile.h"

namespace dae
{
	struct TileSettings
	{
		TileSettings(std::shared_ptr<SDL_Texture> tex, bool walkable, bool changeable = false, Prefab* spawnThis = nullptr, const b2Vec2& texSizeOffset = { 0,0 })
			:texture{tex}
			,isWalkable{walkable}
			,spawnThisOnTile{spawnThis}
			,textureSizeOffset{ texSizeOffset }
			,isChangable{changeable}
		{}

		TileSettings() {};

		std::shared_ptr<SDL_Texture> texture = nullptr;
		bool isWalkable = false;
		bool isChangable = false;
		Prefab* spawnThisOnTile = nullptr;
		//default {0,0}, if > 0 makes the texture bigger than the tile, if < 0 makes the texture smaller 
		b2Vec2 textureSizeOffset{ 0,0 };
	};

	//Tile by amount of connections usefull in some cases...
	struct TileByNrConnections
	{
		TileByNrConnections(unsigned int no, unsigned int one, unsigned int twoStraight, unsigned int twoCorner, unsigned int three, unsigned int four)
			:NoConnectionTileID{ no }
			, OneConnectionTileID{ one }
			, TwoConnectionsStraightTileID{ twoStraight }
			, TwoConnectionsCornerTileID{ twoCorner }
			, ThreeConnectionsTileID{ three }
			, FourConnectionsTileID{ four }
		{
		}
		TileByNrConnections()
			:NoConnectionTileID{ 0 }
			, OneConnectionTileID{ 0 }
			, TwoConnectionsStraightTileID{ 0 }
			, TwoConnectionsCornerTileID{ 0 }
			, ThreeConnectionsTileID{ 0 }
			, FourConnectionsTileID{0}
		
		{};
		unsigned int NoConnectionTileID = 0;
		unsigned int OneConnectionTileID = 0;
		unsigned int TwoConnectionsStraightTileID = 0;
		unsigned int TwoConnectionsCornerTileID = 0;
		unsigned int ThreeConnectionsTileID = 0;
		unsigned int FourConnectionsTileID = 0;
	};

	//rotation based on connections(ROTATES CLOCKWISE!), usefull for: tunnels, roads, etc
	struct TileRotationsByConnections
	{
		unsigned int Up = 0;
		unsigned int Down = 0;
		unsigned int Left = 0;
		unsigned int Right = 0;
		unsigned int UpLeft = 0;
		unsigned int UpRight = 0;
		unsigned int DownLeft = 0;
		unsigned int DownRight = 0;
		unsigned int UpDown = 0;
		unsigned int LeftRight = 0;
		unsigned int UpDownLeft = 0;
		unsigned int UpDownRight = 0;
		unsigned int LeftRightUp = 0;
		unsigned int LeftRightDown = 0;
	};
	class GridLevel final
	{
	public:
		GridLevel(const std::string& levelFilePath, bool usePathfinding, const b2Vec2& offsetFromCenter = { 0,0 });
		GridLevel(const std::string& levelFilePath, bool usePathfinding, const TileByNrConnections& tileNrByCon, const b2Vec2& offsetFromCenter = { 0,0 });
		GridLevel(const std::string& levelFilePath, bool usePathfinding, const TileRotationsByConnections& tileRotByCon, const b2Vec2& offsetFromCenter = { 0,0 });
		GridLevel(const std::string& levelFilePath, bool usePathfinding, const TileRotationsByConnections& tileRotByCon, const TileByNrConnections& tileNrByCon, const b2Vec2& offsetFromCenter = { 0,0 });
		virtual ~GridLevel();

		void Render();
		void Initialize();
		void EnablePathfinding();

		unsigned int GetTileWidth() const { return m_Width / m_HorTiles; };
		unsigned int GetTileHeight() const { return m_Height / m_VertTiles; };

		void AddTileConfiguration(unsigned int id, const TileSettings& tileSettings);

		void AddConnection(GridTile* fromTile, GridTile* toTile);
		//Does a GetTileByPos to determine the from and toTile for the connection, slower!
		void AddConnection(const b2Vec2& fromPos, const b2Vec2& toPos);

		GridTile* GetTileByPos(const b2Vec2& pos, bool clip = true);

	private:
		enum ConnectionDirection
		{
			none = 0,
			left = 3,
			right = 5,
			up = 7,
			down = 11
		};
		std::string m_FilePath;
		unsigned int m_HorTiles;
		unsigned int m_VertTiles;
		unsigned int m_Width;
		unsigned int m_Height;
		const b2Vec2 m_CenterOffset;
		bool m_UsePathfinding;
		bool m_RotateTilesByConnections;
		bool m_SetTileByNrConnections;
		bool m_Initialized;
		std::vector<unsigned int> m_Nrs;
		std::map<const unsigned  int, const TileSettings> m_TilesMap; //this map you link a number from the file to a GridTile class you made
		std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>> m_DirectionCodesForTiles;


		std::vector<GridTile*> m_pGridTiles;

		const TileRotationsByConnections m_TileRotationByConnections;
		const TileByNrConnections m_TileByNrConnections;
		void BuildGridLevel();
		void MakeConnections(bool clearFirst);
		void UpdateTileTextureAndRotation(const std::vector<GridTile*>& gridTilesToChange);
		void BuildDirectionCodesForTiles();

		//returns left-right bool (true = left) and Up-Down bool (up = true)
		ConnectionDirection GetConnectionDirection(unsigned int IdOne, unsigned int IdTwo);
	};
}

