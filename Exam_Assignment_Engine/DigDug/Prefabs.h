#pragma once
#include "Prefab.h"


// add all your components on the m_GameObject variable in the Setup function!

class DigDug : public dae::Prefab
{
public:
	DigDug() = default;
	~DigDug() = default;

	void Setup() override;
};

class Pooka : public dae::Prefab
{
public:
	Pooka() = default;
	~Pooka() = default;

	void Setup() override;
};

class Fygar : public dae::Prefab
{
public:
	Fygar() = default;
	~Fygar() = default;

	void Setup() override;
};
