#pragma once

namespace dae
{
	class GridTile
	{
	public:
		GridTile(std::shared_ptr<SDL_Texture> texture, bool isWalkable, Prefab* spawnOnThisTile = nullptr);
		~GridTile() = default;

	private:
		std::shared_ptr<SDL_Texture> m_pTexture;
		b2Vec2 m_Pos;
		bool m_IsWalkable;
	};
}

