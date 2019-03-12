#pragma once
struct SDL_Texture;

namespace dae
{
	class Texture2D final:
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* m_pTexture;
	};
}
