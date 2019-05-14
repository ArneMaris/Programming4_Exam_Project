#include "MiniginPCH.h"
#include "GridTile.h"
#include "Prefab.h"
#include "GameObject.h"
#include "Renderer.h"

dae::GridTile::GridTile(const b2Vec2& pos, const b2Vec2& size, std::shared_ptr<SDL_Texture> texture, bool isWalkable, Prefab* spawnOnThisTile)
	:m_Pos{pos}
	,m_Size{size}
	,m_IsWalkable{isWalkable}
	,m_pTexture {texture}
{

	if (spawnOnThisTile != nullptr)
	{
		GameObject* obj = spawnOnThisTile->Setup();
		obj->GetTransform()->SetPosition(m_Pos);
		SceneManager::GetInstance().GetActiveScene()->AddGameObject(obj);
	}
}

void dae::GridTile::Render()
{
	b2Vec2 renderPos = m_Pos;
	renderPos.x -= m_Size.x / 2;
	renderPos.y += m_Size.y / 2;
	Renderer::GetInstance().RenderTexture(m_pTexture, renderPos.x, renderPos.y, m_Size.x, m_Size.y);
}
