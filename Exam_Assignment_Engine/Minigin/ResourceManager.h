#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <SDL.h>
#include <SDL_ttf.h>
struct B2Vec2;

#define TextureMapStartSize 30
#define FontMapStartSize 3

namespace dae
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		ResourceManager() = default;

		void Init(const std::string& resourcesPath);
		void CleanUp();

		const std::string& GetResourcesPath() { return m_ResourcesPath; };

		std::shared_ptr<TTF_Font> LoadFont(const std::string& fileName, unsigned int size);
		std::shared_ptr<SDL_Texture> LoadTexture(const std::string& fileName);
		std::vector<b2Vec2> GetVerticesFromSVG(const std::string& fileName);

		const std::string GetTextureName(std::shared_ptr<SDL_Texture> tex);

	private:
		std::string m_ResourcesPath;
		std::unordered_map<std::string, std::shared_ptr<TTF_Font>> m_FontMap{};
		std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> m_TexturesMap{};
	};

}
