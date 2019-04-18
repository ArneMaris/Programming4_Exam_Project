#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "SpriteComponent.h"
#include "Font.h"
#include "SDL.h"

void dae::ResourceManager::Init(std::string&& dataPath)
{
	m_ResourcesPath = std::move(dataPath);

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}

	Logger::LogInfo("ResourcesManager initialize succesfull!");
}

SDL_Texture* dae::ResourceManager::LoadTexture(const std::string& file)
{
	std::string fullPath = m_ResourcesPath + file;
	SDL_Texture* texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	std::pair<std::map<const std::string, SDL_Texture*>::iterator, bool> returnValue;
	returnValue = m_pTexturesMap.insert(std::pair<std::string, SDL_Texture*>(file, texture));
	return returnValue.first->second;
}

dae::Font* dae::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	std::string fullPath = m_ResourcesPath + file;
	Font* font = new Font(fullPath, size);
	if (font == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}

	std::pair<std::map<const std::string, Font*>::iterator, bool> returnValue;
	returnValue = m_pFontMap.insert(std::pair<std::string, Font*>(file, font));
	return returnValue.first->second;
}
