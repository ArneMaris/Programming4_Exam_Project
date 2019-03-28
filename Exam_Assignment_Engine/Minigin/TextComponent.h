#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "SDL.h"

namespace dae
{
	class Font;
	class GameObject;

	class TextComponent final: public BaseComponent
	{
		friend class FpsCounterComponent;
	public:
		void SetText(const std::string& text);
		void SetTextColor(const SDL_Color& color);
		void SetTextOffset(glm::vec2 m_Position);
		const glm::vec2& GetTextOffset() const;

		explicit TextComponent(Font* font, const std::string& text, const SDL_Color& color = { 255,255,255 });
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	protected:
		virtual void Update() override;
		virtual void Render() const override;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Font* m_pFont;
		SDL_Color m_TextColor;
		SDL_Texture* m_pTexture;
		glm::vec2 m_Offset{};
	};

}
