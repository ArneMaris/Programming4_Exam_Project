#pragma once
#include "BaseComponent.h"
struct SDL_Texture;

namespace dae
{
	class SpriteComponent: public BaseComponent
	{
		friend class AnimatedSpriteComponent;
	public:
		SpriteComponent(const std::wstring& assetName, float scale = 1, b2Vec2 offset = { 0,0 });
		virtual ~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent &) = delete;
		SpriteComponent(SpriteComponent &&) = delete;
		SpriteComponent & operator= (const SpriteComponent &) = delete;
		SpriteComponent & operator= (const SpriteComponent &&) = delete;

		void SetSpriteOffset(b2Vec2 newPosition);
		void SetTexture(const std::wstring& assetPathNewTexture);
		const b2Vec2& GetSpriteOffset() const;
		void SetScale(float newScale);

		int GetTextureWidth() const;
		int GetTextureHeight() const;

	protected:
		virtual void Update() override;
		virtual void Render() const override;

		SDL_Texture* m_pTexture;
		b2Vec2 m_Offset;
		int m_TextureWidth;
		int m_TextureHeight;
		float m_Scale;
	};
}
