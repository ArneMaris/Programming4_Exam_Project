#pragma once

namespace dae
{
	class TileConnection;
	class GridTile final
	{
		friend class GridLevel;
	public:
		GridTile(unsigned int id, const b2Vec2& pos, const b2Vec2& size, std::shared_ptr<SDL_Texture> texture, bool isWalkable, bool isChangable = false, Prefab* spawnOnThisTile = nullptr);

		~GridTile();

		void Render();
		const b2Vec2& GetPos() const { return m_Pos; };
		bool GetIsWalkable() const { return m_IsWalkable; };
		bool HasConnectionToTile(unsigned int toTileId);

	private:
		void AddConnection(GridTile* toTile);
		void ClearAllConnections();

		std::shared_ptr<SDL_Texture> m_pTexture;
		unsigned int m_Rotation;
		const b2Vec2 m_Pos;
		bool m_IsWalkable;
		const bool m_IsChangeable;
		const b2Vec2 m_Size;
		const unsigned int m_Id;

		std::vector<TileConnection*> m_pConnections;
	};
}

