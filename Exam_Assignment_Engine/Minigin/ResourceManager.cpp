#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "SpriteComponent.h"
#include "Font.h"
#include "SDL.h"

void dae::ResourceManager::Init(std::wstring&& dataPath)
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

	Logger::LogInfo(L"ResourcesManager initialize succesfull!");
}

SDL_Texture* dae::ResourceManager::LoadTexture(const std::wstring& file)
{
	std::string fullPath = { m_ResourcesPath.begin(), m_ResourcesPath.end() };
	fullPath.append(std::string(file.begin(), file.end()));
	SDL_Texture* texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	std::pair<std::map<const std::wstring, SDL_Texture*>::iterator, bool> returnValue;
	returnValue = m_TexturesMap.insert(std::pair<const std::wstring, SDL_Texture*>(file, texture));
	return returnValue.first->second;
}

dae::Font* dae::ResourceManager::LoadFont(const std::wstring& file, unsigned int size)
{
	std::wstring fullPath = m_ResourcesPath + file;
	Font* font = new Font(fullPath, size);
	if (font == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}

	std::pair<std::map<const std::wstring, Font*>::iterator, bool> returnValue;
	returnValue = m_FontMap.insert(std::pair<const std::wstring, Font*>(file, font));
	return returnValue.first->second;
}
