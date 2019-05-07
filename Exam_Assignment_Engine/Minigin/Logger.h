#pragma once
#include "Singleton.h"
#include "imgui.h"

namespace dae
{
	//took the logger example from imGui demo and modified
	class Logger : public Singleton<Logger>
	{
	public:
		Logger();
		~Logger();

		 void LogWarning(const std::wstring& message);
		 void LogError(const std::wstring& message);
		 void LogInfo(const std::wstring& message);

		 void EnableInfoLogging();
		 void DisableInfoLogging();

		 void Draw(bool* p_open = NULL);

	private:
		 void AddLog(const char* fmt, ...) IM_FMTARGS(2);
		 void Clear();

		 ImGuiTextBuffer     Buf{};
		 ImGuiTextFilter     Filter{};
		 ImVector<int>       LineOffsets{};        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
		bool                AutoScroll;
		bool                ScrollToBottom;

		bool m_logInfo;

		ImVec4 m_CurrColor;
	};
}
