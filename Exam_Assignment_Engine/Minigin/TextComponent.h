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
	class GameObject;

	class TextComponent final: public BaseComponent
	{
	public:
		void SetText(const std::string& text);
		void SetTextOffset(glm::vec2 m_Position);
		const glm::vec2& GetTextOffset() const;

		explicit TextComponent(const std::string& text, Font* font);
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
		Texture2D* m_pTexture;
		glm::vec2 m_Offset{};
	};

}
