#include "MiniginPCH.h"
#include "ScriptComponent.h"
#include "Script.h"

dae::ScriptComponent::ScriptComponent(Script * script)
	:m_pScript{script}
{
}

dae::ScriptComponent::~ScriptComponent()
{
	delete m_pScript;
}


void dae::ScriptComponent::SetNewScript(Script * newScript)
{
	if (m_pScript != newScript)
	{
		delete m_pScript;
		m_pScript = newScript;
		m_pScript->Initialize();
		m_pScript->m_pOwnerObject = m_pGameObject;
	}
}

void dae::ScriptComponent::Update()
{
	m_pScript->Update();
}

void dae::ScriptComponent::Initialize()
{
	if (m_pScript != nullptr)
	{
		m_pScript->m_pOwnerObject = m_pGameObject;
		m_pScript->Initialize();
	}
	else
	{
		Logger::GetInstance().LogError(L"Trying to add an invalid script to scriptComponent!");
	}
}

void dae::ScriptComponent::Render() const
{
	m_pScript->Render();
}

void dae::ScriptComponent::PostRender() const
{
	m_pScript->PostRender();
}
