#pragma once
#include "Singleton.h"
struct SDL_Texture;

namespace dae
{
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::string mDataPath;
	public:
		ResourceManager() = default;

		void Init(std::string&& data);

		SDL_Texture* LoadTexture(const std::string& file);
		Font* LoadFont(const std::string& file, unsigned int size);
	};

}
