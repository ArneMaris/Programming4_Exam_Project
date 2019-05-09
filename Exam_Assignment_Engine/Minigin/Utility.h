#pragma once
#include <memory> // shared_ptr
#include <SDL.h>
#include "SceneManager.h"
#include "Scene.h"

namespace dae
{
	#pragma warning(disable: 4505) //Unreferenced local function has been removed
	static void SDL_DelRes(SDL_Texture  *r) { SDL_DestroyTexture(r); }
	static void SDL_DelRes(SDL_Surface  *r) { SDL_FreeSurface(r); }

	template <typename T>
	std::shared_ptr<T> SDL_SharedPointer(T *t) {
		return std::shared_ptr<T>(t, [](T *t) { SDL_DelRes(t); });
	}

	//----------------------------------------------------------------
	//Global functions for easier acces to some stuff	!SLOW, don't use in UPDATE()!

	//Global function to easily acces GameObjects by their name
	static GameObject* GetGameObjectByName(const std::wstring& name)
	{
		SceneManager::GetInstance().GetActiveScene()->GetGameObject(name);
	};
}