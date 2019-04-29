#pragma once
#include "Singleton.h"

namespace dae
{
	class Logger : public Singleton<Logger>
	{
	public:
		Logger();
		~Logger();

		static void LogWarning(const std::wstring& message);
		static void LogError(const std::wstring& message);
		static void LogInfo(const std::wstring& message);

		static void EnableInfoLogging();
		static void DisableInfoLogging();

		static void EnableInterupOnError();
		static void DisableInterupOnError();

	private:
		static bool m_logInfo;
		static bool m_interuptOnError;
	};
}
