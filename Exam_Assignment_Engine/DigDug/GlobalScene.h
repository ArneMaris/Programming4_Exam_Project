#pragma once
#include <Scene.h>
class GlobalScene : public dae::Scene
{
public:
	GlobalScene();
	~GlobalScene() = default;

	virtual void Update() override;
	virtual void Render() const override;
	virtual void Initialize() override;
};

