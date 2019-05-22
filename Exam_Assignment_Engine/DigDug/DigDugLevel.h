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

	void AddEnemy() {++m_EnemiesLeft;};
	void RemoveEnemy();

private:
	std::string m_LevelPath;
	int m_EnemiesLeft = 0;
};

