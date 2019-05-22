#include "pch.h"
#include "MenuAndHud.h"
#include "ResourceManager.h"
#include "SceneManager.h"

MenuAndHud::MenuAndHud()
	:m_Score{0}
	,m_Lifes{3}
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("ConnectionSerif.otf", 35);

	auto texObj = new dae::GameObject();
	texObj->AddComponent(new dae::TextComponent(font, "SCORE", { 255,0,0 }));
	texObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth / 2), float(dae::GameInfo::windowHeight - 45));
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(texObj);

	//actuall score text (this one will be updated)
	texObj = new dae::GameObject();
	texObj->AddComponent(new dae::TextComponent(font, "0", { 240,240,240 }));
	texObj->GetComponent<dae::TextComponent>()->SetTextOffset({ 0,45 });
	texObj->GetTransform()->SetPosition(float(dae::GameInfo::windowWidth / 2), float(dae::GameInfo::windowHeight - 80));
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(texObj);
	m_pTextComp = texObj->GetComponent<dae::TextComponent>();

	auto lifeObj = new dae::GameObject();
	lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
	lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
	lifeObj->AddComponent(new dae::SpriteComponent("LifeIcon.png"));
	lifeObj->GetTransform()->SetPosition(240, 50);
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(lifeObj);
	m_pLifeSprites = lifeObj->GetComponents<dae::SpriteComponent>();
}


void MenuAndHud::Initialize()
{
	m_pTextComp->SetText(std::to_string(m_Score));
	float xOffset = 0;
	for (auto& spr : m_pLifeSprites)
	{
		spr->SetSpriteOffset({ xOffset,0 });
		spr->SetScale({ 2, 2 });
		spr->SetDoRender(true);
		xOffset += 35;
	}
}

void MenuAndHud::Update()
{

}

void MenuAndHud::Render() const
{

}

void MenuAndHud::PostRender() const
{

}

void MenuAndHud::AddScore(int score)
{
	m_Score += score;
	m_pTextComp->SetText(std::to_string(m_Score));
}

void MenuAndHud::RemoveLife()
{
	if (m_Lifes == 1)
	{
		//UR GAME OVER BITCH
	}
	else
	{
		m_pLifeSprites[m_Lifes - 1]->SetDoRender(false);
		--m_Lifes;
	}
}
