#pragma once
#include "Scene.h"

class DigDugLevel final: public dae::Scene
{
public:
	DigDugLevel(const std::string& levelPath);
	virtual void Update() override;
	virtual void Render() const override;
	virtual void Initialize() override;

	~DigDugLevel() = default;

private:
	std::string m_LevelPath;
};

