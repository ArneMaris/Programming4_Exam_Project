#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject() = default;


//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y)
{
	m_pTransform->SetPosition(x, y, 0.0f);
}

const glm::vec3 dae::GameObject::GetPosition()
{
	return m_pTransform->GetPosition();
}

void dae::GameObject::AddComponent(BaseComponent* pComp)
{
	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = this;
}

void dae::GameObject::RemoveComponent(BaseComponent* pComp)
{
	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);
	m_pComponents.erase(it);
	pComp->m_pGameObject = nullptr;
}

