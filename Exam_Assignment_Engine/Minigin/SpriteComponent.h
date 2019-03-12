#pragma once
struct SDL_Texture;
#include "BaseComponent.h";

namespace dae
{
	class SpriteComponent final: public BaseComponent
	{
		class Texture2D;
	public:
		SpriteComponent(const std::string assetPath);
		~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent &) = delete;
		SpriteComponent(SpriteComponent &&) = delete;
		SpriteComponent & operator= (const SpriteComponent &) = delete;
		SpriteComponent & operator= (const SpriteComponent &&) = delete;
	private:
		std::shared_ptr<Texture2D> m_pTexture2D;
	};
}
