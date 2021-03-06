#pragma once
#include <memory> // shared_ptr
#include "SDL.h"
#include "SDL_ttf.h"
#include "SceneManager.h"
#include "Scene.h"
#include <future>

namespace dae
{
	#pragma warning(disable: 4505) //Unreferenced local function has been removed
	static void SDL_DelRes(SDL_Texture  *r) { SDL_DestroyTexture(r); }
	static void SDL_DelRes(SDL_Surface  *r) { SDL_FreeSurface(r); }
	static void SDL_DelRes(TTF_Font  *r) { TTF_CloseFont(r); }

	template <typename T>
	std::shared_ptr<T> SDL_SharedPointer(T *t) 
	{
		return std::shared_ptr<T>(t, [](T *t) { SDL_DelRes(t); });
	}


	//----------------------------------------------------------------
	//Global functions for easier acces to some stuff	!SLOW, don't use in UPDATE()!

	//Global function to easily acces GameObjects by their name
	static GameObject* GetObjByNameActiveScene(const std::wstring& name)
	{
		return SceneManager::GetInstance().GetActiveScene()->GetGameObject(name);
	};

	static GameObject* GetObjByNameGlobalScene(const std::wstring& name)
	{
		return SceneManager::GetInstance().GetGlobalScene()->GetGameObject(name);
	};

	static std::vector<GameObject*> GetAllObjsInLayerActiveScene(int layer)
	{
		return SceneManager::GetInstance().GetActiveScene()->GetGameObjectsInLayer(layer);
	};

	static std::vector<GameObject*> GetAllObjsInLayerGlobalScene(int layer)
	{
		return SceneManager::GetInstance().GetGlobalScene()->GetGameObjectsInLayer(layer);
	};
}
	static float RadToDegrees(float angleInRad)
	{
		return angleInRad * 180 / float(M_PI);
	}

	static double RadToDegrees(double angleInRad)
	{
		return angleInRad * 180 / M_PI;
	}

	static float DegreesToRad(float angleInDegrees)
	{
		return angleInDegrees * float(M_PI) / 180.0f;
	}

	static double DegreesToRad(double angleInDegrees)
	{
		return angleInDegrees * M_PI / 180.0;
	}