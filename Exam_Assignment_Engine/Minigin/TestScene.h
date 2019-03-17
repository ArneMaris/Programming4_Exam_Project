#pragma once
#include "Scene.h"

class TestScene final: public dae::Scene
{
public:
	TestScene(bool autoInit = true);
	virtual void Update() override;
	virtual void Render() const override;
	virtual void Initialize() override;

	~TestScene() = default;
};

