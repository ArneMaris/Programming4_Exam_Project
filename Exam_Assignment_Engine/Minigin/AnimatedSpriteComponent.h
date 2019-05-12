// MADE USING MY PROGRAMMING 1-2 SPRITESHEET CODE AS REFERENCE
#pragma once
#include "SpriteComponent.h"
#include "SDL.h"
#include <map>

namespace dae
{
	class AnimationResponse;
		struct Animation
		{
			Animation(const std::wstring& name, float secPerFrame = 0.1f, int minrow = 0, int maxrow = 10, int mincolumn = 0, int maxcolumn = 10, AnimationResponse* animresponse = nullptr)
				: minRow{ minrow }
				, maxColumn{ maxcolumn }
				, minColumn{ mincolumn }
				, maxRow{ maxrow }
				, secPerFrame{ secPerFrame }
				, animationName{std::move(name)}
				, animResponse{ animresponse }
			{}
			const int minRow;
			const int maxRow;
			const int minColumn;
			const int maxColumn;
			const float secPerFrame;
			std::wstring animationName;
			AnimationResponse* animResponse;
		};
	class AnimatedSpriteComponent final : public SpriteComponent
	{
	public:
		enum FlipDirection
		{
			none,
			vertical,
			horizontal
		};
		AnimatedSpriteComponent(const std::wstring& assetName, int nrCols, int nrRows, 
			float scale = 1, float secPerFrame = 0.1f, const b2Vec2& offset = { 0,0 },
			const FlipDirection& flipDir = FlipDirection::none, float angle = 0, const b2Vec2& rotationCenter = { 0,0 });

		AnimatedSpriteComponent(const std::wstring& assetName, int nrCols, int nrRows, float secPerFrame);

		~AnimatedSpriteComponent();
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
		void SetSecondsPerFrame(float newSecPerFrame);

		void AddAnimation(const Animation& animation, bool autoPlay = true);
		void PlayAnimation(const std::wstring& name);
		void ResetAnimationEventTriggers();

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;

	private:
		void SetRowLimit(int min, int max);
		void SetColumnLimit(int min, int max);
		int GetNrFrames() const;

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
		SDL_Point m_RotationCenter;
		FlipDirection m_FlipDirection;
		std::map<const std::wstring, const Animation> m_Animations;

		AnimationResponse* m_pCurrAnimationResponse;
	};
}


