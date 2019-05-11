#include "MiniginPCH.h"
#include "GridTile.h"
#include "Prefab.h"
#include "GameObject.h"

dae::GridTile::GridTile(std::shared_ptr<SDL_Texture> texture, bool isWalkable, Prefab* spawnOnThisTile)
{
	m_pTexture = texture;
	m_IsWalkable = isWalkable;
	if (spawnOnThisTile != nullptr)
	{
		GameObject* obj = spawnOnThisTile->Setup();
		obj->GetTransform()->SetPosition(m_Pos);
		SceneManager::GetInstance().GetActiveScene()->AddGameObject(obj);
	}
}
