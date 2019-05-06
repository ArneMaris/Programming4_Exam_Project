#pragma once
#include "BaseComponent.h"
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
		void SetTextOffset(b2Vec2 newOffset);
		const b2Vec2& GetTextOffset() const;

		explicit TextComponent(std::shared_ptr<Font> font, const std::string& text, const SDL_Color& color = { 255,255,255 });
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		SDL_Color m_TextColor;
		std::shared_ptr<SDL_Texture> m_pTexture;
		b2Vec2 m_Offset{};
	};

}
