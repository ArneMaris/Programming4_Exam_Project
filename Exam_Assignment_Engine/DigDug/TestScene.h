#pragma once
#include "Scene.h"

class TestScene final: public dae::Scene
{
public:
	TestScene();
	virtual void Update() override;
	virtual void Render() const override;
	virtual void Initialize() override;

	~TestScene() = default;

private:
	dae::GameObject* m_pDigDug;
	dae::GameObject* obj2;
};

