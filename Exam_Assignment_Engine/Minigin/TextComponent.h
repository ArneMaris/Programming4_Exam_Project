#pragma once
#include "TransformComponent.h"
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;

	class TextComponent final: public BaseComponent
	{
	public:
		void Update();
		void Render() const;

		void SetText(const std::string& text);

		explicit TextComponent(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:

		bool mNeedsUpdate;
		std::string mText;
		std::shared_ptr<Font> mFont;
		std::shared_ptr<Texture2D> mTexture;

		GameObject* m_pGameObject; // the gameObject this component is attached too;
	};

}
