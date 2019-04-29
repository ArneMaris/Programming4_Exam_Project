#pragma once
#include <SDL_ttf.h>

namespace dae
{
	class Font
	{
	public:
		TTF_Font* GetFont() const;
		explicit Font(const std::wstring& fullPath, unsigned int size);
		~Font();

		unsigned int GetFontSize() const;
		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
	private:
		TTF_Font* m_Font;
		unsigned int m_Size;
	};

}
