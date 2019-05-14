#pragma once

namespace dae
{

	class TileConnection;
	class GridTile final
	{
	public:
		GridTile(const b2Vec2& pos, const b2Vec2& size, std::shared_ptr<SDL_Texture> texture, bool isWalkable, Prefab* spawnOnThisTile = nullptr);
		~GridTile() = default;

		void Render();
		void AddConnection(GridTile* toTile);

		bool GetIsWalkable() const { return m_IsWalkable; };

	private:
		std::shared_ptr<SDL_Texture> m_pTexture;
		const b2Vec2 m_Pos;
		const bool m_IsWalkable;
		const b2Vec2 m_Size;

		std::vector<TileConnection*> m_pConnections;
	};
}

