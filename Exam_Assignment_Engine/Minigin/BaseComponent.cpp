#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent* dae::BaseComponent::GetTransform() const
{
	return m_pGameObject->GetTransform();
}
