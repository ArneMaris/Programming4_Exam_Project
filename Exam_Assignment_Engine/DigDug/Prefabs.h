#pragma once
#include "Prefab.h"
class DigDug : public dae::Prefab
{
public:
	DigDug() = default;
	~DigDug() = default;

	dae::GameObject* Setup() override;
};

class Pooka : public dae::Prefab
{
public:
	Pooka() = default;
	~Pooka() = default;

	dae::GameObject* Setup() override;
};

