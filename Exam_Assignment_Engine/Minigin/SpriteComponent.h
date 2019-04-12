#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
struct SDL_Texture;

namespace dae
{
	class SpriteComponent: public BaseComponent
	{
		friend class AnimatedSpriteComponent;
	public:
		SpriteComponent(const std::string& assetName, float scale = 1, glm::vec2 offset = { 0,0 });
		virtual ~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent &) = delete;
		SpriteComponent(SpriteComponent &&) = delete;
		SpriteComponent & operator= (const SpriteComponent &) = delete;
		SpriteComponent & operator= (const SpriteComponent &&) = delete;

		void SetSpriteOffset(glm::vec2 newPosition);
		void SetTexture(const std::string& assetPathNewTexture);
		const glm::vec2& GetSpriteOffset() const;
		void SetScale(float newScale);

		int GetTextureWidth() const;
		int GetTextureHeight() const;

	protected:
		virtual void Update() override;
		virtual void Render() const override;

		SDL_Texture* m_pTexture;
		glm::vec2 m_Offset{};
		int m_TextureWidth;
		int m_TextureHeight;
		float m_Scale;
	};
}
