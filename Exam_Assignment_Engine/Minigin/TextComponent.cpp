#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "SpriteComponent.h"
#include "GameObject.h"


dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
	: mNeedsUpdate(true)
	, mText(text)
	, mFont(font)
	, mTexture(nullptr)
{ 
}

void dae::TextComponent::Update()
{
	if (mNeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		mTexture = std::make_shared<Texture2D>(texture);
	}
}

void dae::TextComponent::Render() const
{
	if (mTexture != nullptr)
	{
		const auto pos = m_pGameObject->GetPosition();
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	mText = text;
	mNeedsUpdate = true;
}


