#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"


std::shared_ptr<dae::TransformComponent> dae::BaseComponent::GetTransform() const
{
	return m_pGameObject->GetTransform();
}

void dae::BaseComponent::Render() const
{
}

