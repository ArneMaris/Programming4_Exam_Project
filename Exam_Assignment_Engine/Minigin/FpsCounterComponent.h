#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	class Font;
	class Texture2D;
	class FpsCounterComponent final : public BaseComponent
	{
	public:
		enum class Corner
		{
			leftTop,
			rightTop,
			leftBot,
			rightBot
		};

		explicit FpsCounterComponent(Font* font, Corner corner = Corner::leftTop);
		virtual ~FpsCounterComponent() = default;
		FpsCounterComponent(const FpsCounterComponent& other) = delete;
		FpsCounterComponent(FpsCounterComponent&& other) = delete;
		FpsCounterComponent& operator=(const FpsCounterComponent& other) = delete;
		FpsCounterComponent& operator=(FpsCounterComponent&& other) = delete;

	protected:
		virtual void Update() override;
		virtual void Render() const override;

	private:
		Font* m_pFont;
		Texture2D* m_pTexture;
		int m_FPS;
		float m_FpsTimer;
		int m_FpsCount;
		Corner m_Corner;
	};
}

