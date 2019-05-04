#pragma once
#include "Singleton.h"
#include <map>
#include <SDL.h>
struct B2Vec2;

namespace dae
{
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::wstring m_ResourcesPath;
	public:
		ResourceManager() = default;

		void CleanUp();

		void Init(std::wstring&& resourcesPath);

		std::shared_ptr<Font> LoadFont(const std::wstring& fileName, unsigned int size);
		std::map<std::wstring, std::shared_ptr<Font>> m_FontMap{};

		std::shared_ptr<SDL_Texture> LoadTexture(const std::wstring& fileName);
		std::map<const std::wstring, std::shared_ptr<SDL_Texture>> m_TexturesMap{};

		std::vector<b2Vec2> GetVerticesFromSVG(const std::wstring& fileName);

	};

}
