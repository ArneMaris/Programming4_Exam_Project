#pragma once
#include "GameObject.h"

//class that holds a GameObject and all its component (sort of premade GameObjects)
//this can be used to easily reproduce multiple instances of the same GameObject (enemies, projectiles, etc...)

namespace dae
{
	class Prefab
	{
	public:
		explicit Prefab() { Logger::GetInstance().LogInfo(L"PREFAB MADE"); m_GameObject = new GameObject();};
		virtual ~Prefab() = default;
		Prefab(const Prefab& InputAction) = delete;
		Prefab(Prefab&& InputAction) = delete;
		Prefab& operator=(const Prefab& other) = delete;
		Prefab& operator=(Prefab&& other) = delete;

		virtual GameObject* Setup() = 0;
	protected:
		GameObject* m_GameObject;
	};
}

