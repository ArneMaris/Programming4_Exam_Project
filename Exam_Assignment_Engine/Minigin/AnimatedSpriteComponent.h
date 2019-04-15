// MADE USING MY PROGRAMMING 1-2 SPRITESHEET CODE AS REFERENCE
#pragma once
#include "SpriteComponent.h"
struct SDL_Texture;

namespace dae
{
	class AnimatedSpriteComponent final : public SpriteComponent
	{
	public:
		enum FlipDirection
		{
			none,
			vertical,
			horizontal,
			both
		};
		AnimatedSpriteComponent(const std::string& assetName, int nrCols, int nrRows, 
			float scale = 1, float secPerFrame = 0.1f, int startRow = 1, int startColumn = 1, const b2Vec2& offset = { 0,0 },
			const FlipDirection& flipDir = FlipDirection::none, float angle = 0, const b2Vec2& rotationCenter = { 0,0 });

		AnimatedSpriteComponent(const std::string& assetName, int nrCols, int nrRows, float secPerFrame);

		~AnimatedSpriteComponent() = default;
		AnimatedSpriteComponent(const AnimatedSpriteComponent& other) = delete;
		AnimatedSpriteComponent(AnimatedSpriteComponent&& other) = delete;
		AnimatedSpriteComponent& operator=(const AnimatedSpriteComponent& other) = delete;
		AnimatedSpriteComponent& operator=(AnimatedSpriteComponent&& other) = delete;

		void SetFlipDirection(const FlipDirection& flipDir);
		void SetAngleDegrees(float newAngle);
		void SetAngleRadians(float newAngle);
		void SetRotationCenter(b2Vec2 newCenter);
		void SetActiveRow(int newRow, bool reset = true);
		void SetActiveColumn(int newColumn, bool reset = true);
		void SetRowLimit(int min, int max);
		void SetColumnLimit(int min, int max);
		void SetSecondsPerFrame(float newSecPerFrame);

	protected:
		virtual void Update() override;
		virtual void Render() const override;

	private:
		const int m_Cols;
		const int m_Rows;
		float m_SecPerFrame;
		float m_AccuSec;
		int m_MinRow;
		int m_MaxRow;
		int m_MinColumn;
		int m_MaxColumn;

		int m_CurrRow;
		int m_CurrColumn;

		float m_Angle;
		b2Vec2 m_RotationCenter;
		FlipDirection m_FlipDirection;

		int GetNrFrames() const;

	};
}


