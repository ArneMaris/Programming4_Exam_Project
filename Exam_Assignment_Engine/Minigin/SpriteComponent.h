#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
struct SDL_Texture;

namespace dae
{
	class SpriteComponent final: public BaseComponent
	{
	public:
		SpriteComponent(const std::string assetPath);
		~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent &) = delete;
		SpriteComponent(SpriteComponent &&) = delete;
		SpriteComponent & operator= (const SpriteComponent &) = delete;
		SpriteComponent & operator= (const SpriteComponent &&) = delete;

		void SetSpriteOffset(glm::vec2 newPosition);
		const glm::vec2& GetSpriteOffset() const;

	protected:
		virtual void Update() override;
		virtual void Render() const override;

	private:
		SDL_Texture* m_pTexture;
		glm::vec2 m_Offset{};
	};
}