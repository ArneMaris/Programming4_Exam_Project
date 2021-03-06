#include "MiniginPCH.h"
#include "GridTile.h"
#include "Prefab.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TileConnection.h"
#include "PhysicsDebugDrawer.h"
#include "ResourceManager.h"


dae::GridTile::GridTile(Scene* scene, unsigned int id, const b2Vec2& pos, const b2Vec2& size, std::shared_ptr<SDL_Texture> texture, bool isWalkable, bool isChangable, Prefab* spawnOnThisTile)
	:m_Pos{pos}
	,m_Size{size}
	,m_IsWalkable{isWalkable}
	,m_pTexture {texture}
	,m_IsChangeable{ isChangable }
	,m_Id{ id }
	,m_Rotation{0}
{

	if (spawnOnThisTile != nullptr)
	{
		GameObject* obj = spawnOnThisTile->RootSetup();
		obj->GetTransform()->SetPosition(m_Pos);
		scene->AddGameObject(obj);
	}
}

dae::GridTile::~GridTile()
{
	for (auto it = m_pConnections.begin(); it != m_pConnections.end(); ++it)
	{
		delete (*it);
	}
	m_pConnections.clear();
}

void dae::GridTile::Render()
{
	b2Vec2 renderPos = m_Pos;
	renderPos.x -= m_Size.x / 2;
	renderPos.y += m_Size.y / 2;

	if (m_Rotation != 0)
	{
		Renderer::GetInstance().RenderTexture(m_pTexture, renderPos.x, renderPos.y, m_Size.x, m_Size.y, float(m_Rotation));
	}
	else
	{
		Renderer::GetInstance().RenderTexture(m_pTexture, renderPos.x, renderPos.y, m_Size.x, m_Size.y);
	}
}

bool dae::GridTile::HasConnectionToTile(unsigned int toTileId)
{
	for (auto& con : m_pConnections)
	{
		if (toTileId == con->GetBack()->m_Id)
			return true;
	}
	return false;
}

bool dae::GridTile::HasConnectionToTile(GridTile * toTile)
{
	for (auto& con : m_pConnections)
	{
		if (toTile->m_Id == con->GetBack()->m_Id)
			return true;
	}
	return false;
}

const std::string dae::GridTile::GetTextureName()
{
	return ResourceManager::GetInstance().GetTextureName(m_pTexture);
}

void dae::GridTile::AddConnection(GridTile * toTile)
{
	m_pConnections.push_back(new TileConnection(this, toTile));
}

void dae::GridTile::ClearAllConnections()
{
	for (auto& con : m_pConnections)
	{
		delete con;
	}
	m_pConnections.clear();
	m_pConnections.shrink_to_fit();
}
