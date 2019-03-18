#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

struct SDL_Texture;

namespace dae
{
	class Font;
	class FpsCounterComponent final : public BaseComponent
	{
	public:
		explicit FpsCounterComponent(Font* font, bool leftTopCorner = true);
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
		SDL_Texture* m_pTexture;
		bool m_LeftTop;

		int m_FPS;
		float m_FpsTimer;
		int m_FpsCount;
	};
}

