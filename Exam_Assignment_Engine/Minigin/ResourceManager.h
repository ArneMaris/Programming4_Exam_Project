#pragma once
#include "Singleton.h"
#include <unordered_map>
struct SDL_Texture;

namespace dae
{
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::string m_ResourcesPath;
	public:
		ResourceManager() = default;

		void Init(std::string&& resourcesPath);

		Font* LoadFont(const std::string& fileName, unsigned int size);
		std::unordered_map<const std::string, Font*> m_pFontMap;

		SDL_Texture* LoadTexture(const std::string& fileName);
		std::unordered_map<const std::string, SDL_Texture*> m_pTexturesMap;

	};

}
