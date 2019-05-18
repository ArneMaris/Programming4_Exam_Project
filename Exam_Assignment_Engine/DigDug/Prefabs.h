#pragma once
#include "Prefab.h"
class DigDug : public dae::Prefab
{
public:
	DigDug() = default;
	~DigDug() = default;

	dae::GameObject* Setup() override;
};

