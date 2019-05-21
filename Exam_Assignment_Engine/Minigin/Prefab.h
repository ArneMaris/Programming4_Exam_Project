#pragma once
#include "GameObject.h"

//Derive this class and override Setup() function.
//add all your components on the m_GameObject variable in the Setup function!
//this can be used to easily reproduce multiple instances of the same GameObject (enemies, projectiles, etc...)

namespace dae
{
	class Prefab
	{
	public:
		Prefab() = default;
		virtual ~Prefab() = default;
		Prefab(const Prefab& InputAction) = delete;
		Prefab(Prefab&& InputAction) = delete;
		Prefab& operator=(const Prefab& other) = delete;
		Prefab& operator=(Prefab&& other) = delete;

		GameObject* RootSetup()
		{
			Logger::GetInstance().LogInfo(L"PREFAB MADE");
			m_GameObject = new GameObject();
			Setup();
			return m_GameObject;
		};
		virtual void Setup() = 0;
	protected:
		GameObject* m_GameObject;
	};
}

