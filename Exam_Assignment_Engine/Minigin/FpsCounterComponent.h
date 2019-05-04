#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
	class Font;
	class FpsCounterComponent final : public BaseComponent
	{
	public:
		explicit FpsCounterComponent(std::shared_ptr<Font> font, bool leftTopCorner = true);
		~FpsCounterComponent() = default;
		FpsCounterComponent(const FpsCounterComponent& other) = delete;
		FpsCounterComponent(FpsCounterComponent&& other) = delete;
		FpsCounterComponent& operator=(const FpsCounterComponent& other) = delete;
		FpsCounterComponent& operator=(FpsCounterComponent&& other) = delete;

	protected:
		virtual void Update() override;
		virtual void Render() const override;

	private:
		TextComponent* m_pTextComp;
		bool m_LeftTop;

		int m_FPS;
		float m_FpsTimer;
		int m_FpsCount;
	};
}

