#pragma once
#include "BaseComponent.h"

namespace dae
{
	class SpriteComponent: public BaseComponent
	{
		friend class AnimatedSpriteComponent;
	public:
		SpriteComponent(const std::string& assetPath, const b2Vec2& scale = { 1,1 }, const b2Vec2& offset = { 0,0 }, float angle = 0, const b2Vec2& rotationCenter = { 0,0 }, const SDL_RendererFlip& flipDir = SDL_FLIP_NONE);
		virtual ~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent &) = delete;
		SpriteComponent(SpriteComponent &&) = delete;
		SpriteComponent & operator= (const SpriteComponent &) = delete;
		SpriteComponent & operator= (const SpriteComponent &&) = delete;

		void SetSpriteOffset(const b2Vec2&  newPosition);
		void SetTexture(const std::string& assetPathNewTexture);
		void SetScale(const b2Vec2& newScale);
		void SetFlipDirection(const SDL_RendererFlip& flipDir);
		void SetAngleDegrees(float newAngle);
		void SetAngleRadians(float newAngle);
		void SetRotationCenter(b2Vec2 newCenter);
		void SetDoRender(bool value) {m_DoRender = value;};

		const b2Vec2& GetSpriteOffset() const;
		int GetTextureWidth() const;
		int GetTextureHeight() const;
		float GetAngleDegrees() const { return m_Angle; };
		float GetAngleRadians() const { return DegreesToRad(m_Angle); };
		SDL_RendererFlip GetRenderFlip() const { return m_FlipDirection; };

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;

		bool m_DoRender;

		std::shared_ptr<SDL_Texture> m_pTexture;
		b2Vec2 m_Offset;
		int m_TextureWidth;
		int m_TextureHeight;

		b2Vec2 m_Scale;
		float m_Angle;
		SDL_Point m_RotationCenter;
		SDL_RendererFlip m_FlipDirection;
	};
}
