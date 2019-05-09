#pragma once
#include "Prefab.h"
class ExamplePrefab : public dae::Prefab
{
public:
	ExamplePrefab() = default;
	~ExamplePrefab() = default;

	dae::GameObject* Setup() override;
};

