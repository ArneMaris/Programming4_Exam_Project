#include "pch.h"
#include "MenuInputResponses.h"
#include "Components.h"
#include "MenuAndHud.h"

void MenuInput::KeyUp::ExecuteOnPress()
{
	static_cast<MenuAndHud*>(dae::GetObjByNameGlobalScene(L"MenuHud")->GetComponent<dae::ScriptComponent>()->GetScript())->MoveUp();
}

void MenuInput::KeyUp::ExecuteOnRelease()
{

}

void MenuInput::KeyDown::ExecuteOnPress()
{
	static_cast<MenuAndHud*>(dae::GetObjByNameGlobalScene(L"MenuHud")->GetComponent<dae::ScriptComponent>()->GetScript())->MoveDown();
}

void MenuInput::KeyDown::ExecuteOnRelease()
{

}

void MenuInput::Stick::ExecuteOnPress()
{
	m_Pressed = true;
}

void MenuInput::Stick::ExecuteOnHold(const b2Vec2 axisValues)
{
	UNREFERENCED_PARAMETER(axisValues);
	if (m_Pressed)
	{
		if (axisValues.y > 0)
			static_cast<MenuAndHud*>(dae::GetObjByNameGlobalScene(L"MenuHud")->GetComponent<dae::ScriptComponent>()->GetScript())->MoveUp();
		else
			static_cast<MenuAndHud*>(dae::GetObjByNameGlobalScene(L"MenuHud")->GetComponent<dae::ScriptComponent>()->GetScript())->MoveDown();

		m_Pressed = false;
	}
}

void MenuInput::Stick::ExecuteOnRelease()
{

}

void MenuInput::Confirm::ExecuteOnPress()
{
	static_cast<MenuAndHud*>(dae::GetObjByNameGlobalScene(L"MenuHud")->GetComponent<dae::ScriptComponent>()->GetScript())->Confirm();
}

void MenuInput::Confirm::ExecuteOnRelease()
{
}
