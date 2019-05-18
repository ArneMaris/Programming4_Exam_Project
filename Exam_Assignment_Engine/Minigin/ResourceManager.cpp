#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL_image.h>

#include "Renderer.h"
#include "SpriteComponent.h"

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"


void dae::ResourceManager::CleanUp()
{
	m_TexturesMap.clear();
	m_FontMap.clear();
}



void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_ResourcesPath = std::move(dataPath);
	m_TexturesMap.reserve(TextureMapStartSize);
	m_FontMap.reserve(FontMapStartSize);

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

	Logger::GetInstance().LogInfo(L"ResourcesManager initialize succesfull!");
}

std::shared_ptr<SDL_Texture> dae::ResourceManager::LoadTexture(const std::string& file)
{
	std::string fullPath = m_ResourcesPath + std::move(file);
	auto texture = SDL_SharedPointer(IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str()));
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	std::pair<std::unordered_map<const std::string, std::shared_ptr<SDL_Texture>>::iterator, bool> returnValue;
	returnValue = m_TexturesMap.insert(std::make_pair(file, texture));
	return returnValue.first->second;
}


std::shared_ptr<TTF_Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	std::string fullPath = m_ResourcesPath + std::move(file);
	std::shared_ptr<TTF_Font> font = SDL_SharedPointer(TTF_OpenFont(fullPath.c_str(), size));
	if (font == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}

	std::pair<std::unordered_map<const std::string, std::shared_ptr<TTF_Font>>::iterator, bool> returnValue;
	returnValue = m_FontMap.insert(std::make_pair(file, font));
	return returnValue.first->second;
}

std::vector<b2Vec2> dae::ResourceManager::GetVerticesFromSVG(const std::string & fileName)
{
	std::vector<b2Vec2> vertices{};
	std::string fullPath = m_ResourcesPath + std::move(fileName);

	//Sample code from NANOSVG documentation
	NSVGimage* image;
	image = nsvgParseFromFile(fullPath.c_str(), "px", 96);
	for (NSVGshape *shape = image->shapes; shape != nullptr; shape = shape->next)
	{
		for (NSVGpath *path = shape->paths; path != nullptr; path = path->next) 
		{
			for (int i = 0; i < path->npts - 1; i += 3) 
			{
				float* p = &path->pts[i * 2];
				vertices.push_back({ p[0], p[1] });
			}
		}
	}
	nsvgDelete(image);

	return vertices;
}
