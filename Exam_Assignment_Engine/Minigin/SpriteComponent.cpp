#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
struct SDL_Texture;


dae::SpriteComponent::SpriteComponent(const std::string assetPath)
{
	m_pTexture2D = std::make_shared<Texture2D>(ResourceManager::GetInstance().LoadTexture(assetPath));
}
