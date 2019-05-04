#pragma once
#include "Scene.h"

class TestScene final: public dae::Scene
{
public:
	TestScene();
	virtual void Update() override;
	virtual void Render() const override;
	virtual void Initialize() override;
	virtual void OnCollisionStart() override;
	virtual void OnCollisionEnd() override;

	~TestScene() = default;
};

