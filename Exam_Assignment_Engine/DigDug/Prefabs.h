#pragma once
#include "Prefab.h"


// add all your components on the m_GameObject variable in the Setup function!

class DigDug : public dae::Prefab
{
public:
	DigDug(bool playerOne = true) :m_PlayerOne{ playerOne } {};
	~DigDug() = default;

	void Setup() override;

private:
	bool m_PlayerOne;
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

	void BuildPlayerFygar();
	void BuildEnemyFygar();
};

class FygarFlame : public dae::Prefab
{
public:
	FygarFlame(SDL_RendererFlip flipDir, const b2Vec2& pos) : m_Flip{ flipDir }, m_Pos{ pos } {};
	~FygarFlame() = default;

	void Setup() override;
private:
	SDL_RendererFlip m_Flip;
	b2Vec2 m_Pos;
};

class Stone : public dae::Prefab
{
public:
	Stone() = default;
	~Stone() = default;

	void Setup() override;
};
