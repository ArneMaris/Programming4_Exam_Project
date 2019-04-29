#pragma once
#include "Singleton.h"
#include <map>
struct SDL_Texture;

namespace dae
{
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::wstring m_ResourcesPath;
	public:
		ResourceManager() = default;

		void Init(std::wstring&& resourcesPath);

		Font* LoadFont(const std::wstring& fileName, unsigned int size);
		std::map<std::wstring, Font*> m_FontMap{};

		SDL_Texture* LoadTexture(const std::wstring& fileName);
		std::map<const std::wstring, SDL_Texture*> m_TexturesMap{};

	};

}
