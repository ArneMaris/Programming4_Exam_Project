#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"


dae::BaseComponent::BaseComponent()
{
}

dae::TransformComponent* dae::BaseComponent::GetTransform() const
{
	return m_pGameObject->GetTransform();
}
