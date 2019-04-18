#pragma once
#include "Singleton.h"

namespace dae
{
	class Logger : public Singleton<Logger>
	{
	public:
		Logger() = default;
		~Logger() = default;

		static void LogWarning(const std::string& message);
		static void LogError(const std::string& message);
		static void LogInfo(const std::string& message);

		static void EnableInfoLogging();
		static void DisableInfoLogging();

		static void EnableInterupOnError();
		static void DisableInterupOnError();

	private:
		static bool m_logInfo;
		static bool m_interuptOnError;
	};
}
