#pragma once
#include "Response.h"

namespace dae
{
	class AnimationResponse final : public Response
	{
	public:
		AnimationResponse(std::pair<int, int> rowColumnWhenToTrigger, bool autoreset)
			:m_RowColumnTrigger{ rowColumnWhenToTrigger }
			, m_AutoReset{ autoreset }
			, m_IsTriggered{ false }
		{};
		AnimationResponse(int rowWhenToTrigger, int ColumnWhenToTrigger, bool autoreset)
			: m_RowColumnTrigger{ std::make_pair(rowWhenToTrigger,ColumnWhenToTrigger) }
			, m_AutoReset{ autoreset }
			, m_IsTriggered{ false }
		{};
		AnimationResponse()
			: m_RowColumnTrigger{ std::make_pair(-1,-1) }
			, m_AutoReset{ false }
			, m_IsTriggered{ false }
		{};
		virtual ~AnimationResponse() = default;

		void Update(int row, int column)
		{
			if (!m_IsTriggered)
			{
				if (m_RowColumnTrigger.first == row && m_RowColumnTrigger.second == column)
				{
					m_IsTriggered = true;
					Notify(NotifyEvent{ NotifyEvent::AnimationResponseTriggered });
				}
			}
			else if (m_AutoReset)
			{
				m_IsTriggered = false;
			}
		}

		void ResetTrigger() { m_IsTriggered = false; };
	private:
		std::pair<int, int> m_RowColumnTrigger;
		bool m_AutoReset;
		bool m_IsTriggered;
	};
}
