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
			Animation(const std::wstring& name, int minrow, int maxrow, int mincolumn, int maxcolumn, float secPerFrame = 0.2f, AnimationResponse* animresponse = nullptr)
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
		AnimatedSpriteComponent(const std::string& assetName, unsigned int nrCols, unsigned int nrRows,
			const b2Vec2 scale = { 1,1 }, float secPerFrame = 0.1f, const b2Vec2& offset = { 0,0 },
			const SDL_RendererFlip& flipDir = SDL_FLIP_NONE, float angle = 0, const b2Vec2& rotationCenter = { 0,0 });

		AnimatedSpriteComponent(const std::string& assetName, unsigned int nrCols, unsigned int nrRows, float secPerFrame);

		~AnimatedSpriteComponent();
		AnimatedSpriteComponent(const AnimatedSpriteComponent& other) = delete;
		AnimatedSpriteComponent(AnimatedSpriteComponent&& other) = delete;
		AnimatedSpriteComponent& operator=(const AnimatedSpriteComponent& other) = delete;
		AnimatedSpriteComponent& operator=(AnimatedSpriteComponent&& other) = delete;

		void SetPaused(bool value) {m_Paused = value;};
		void SetActiveRow(unsigned int newRow, bool reset = true);
		void SetActiveColumn(unsigned int newColumn, bool reset = true);
		void SetSecondsPerFrame(float newSecPerFrame);

		void AddAnimation(const Animation& animation, bool autoPlay = true);
		bool PlayAnimation(const std::wstring& name);
		void ResetAnimationEventTriggers();

		const SDL_RendererFlip& GetFlipDirection() const { return m_FlipDirection; };

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;

	private:
		void SetRowLimit(unsigned int min, unsigned int max);
		void SetColumnLimit(unsigned int min, unsigned int max);
		unsigned int GetNrFrames() const;

		const unsigned int m_Cols;
		const unsigned int m_Rows;
		float m_SecPerFrame;
		float m_AccuSec;
		unsigned int m_MinRow;
		unsigned int m_MaxRow;
		unsigned int m_MinColumn;
		unsigned int m_MaxColumn;

		unsigned int m_CurrRow;
		unsigned int m_CurrColumn;

		bool m_Paused;

		std::map<const std::wstring, const Animation> m_Animations;

		AnimationResponse* m_pCurrAnimationResponse;
	};
}


