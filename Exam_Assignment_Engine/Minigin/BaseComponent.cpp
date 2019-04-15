#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent* dae::BaseComponent::GetTransform() const
{
	return m_pGameObject->GetTransform();
}

void dae::BaseComponent::Render() const
{
}

void dae::BaseComponent::FixedUpdate()
{
	//
}

