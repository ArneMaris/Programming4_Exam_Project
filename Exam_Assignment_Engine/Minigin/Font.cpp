#include "MiniginPCH.h"
#include "Font.h"

TTF_Font* dae::Font::GetFont() const {
	return m_Font;
}

dae::Font::Font(const std::wstring& fullPath, unsigned size) : m_Font(nullptr), m_Size(size)
{
	std::string pathStr = { fullPath.begin(), fullPath.end() };
	m_Font = TTF_OpenFont(pathStr.c_str(), size);
	if (m_Font == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

dae::Font::~Font()
{
	TTF_CloseFont(m_Font);
}

unsigned int dae::Font::GetFontSize() const
{
	return m_Size;
}
