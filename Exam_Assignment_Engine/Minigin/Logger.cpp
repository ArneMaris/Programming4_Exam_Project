#include "MiniginPCH.h"
#include "Logger.h"
#include <thread>

bool dae::Logger::m_logInfo{ false };
bool dae::Logger::m_interuptOnError{ false };

void dae::Logger::LogWarning(const std::string& message)
{
	std::thread warning([message]
		{
			MessageBox(NULL, message.c_str(), "Warning, be carefull!", MB_ICONWARNING);
		});
	warning.detach();
}

void dae::Logger::LogError(const std::string& message)
{
	if (!m_interuptOnError)
	{
		std::thread error([message]
			{
				MessageBox(NULL, message.c_str(), "Error, you should shut down!", MB_ICONERROR);
			});
		error.detach();
	}
	else
	{
		MessageBox(NULL, message.c_str(), "Error, you should shut down!", MB_ICONERROR);
	}
}

void dae::Logger::LogInfo(const std::string& message)
{
	if (m_logInfo)
	{
		std::thread info([message]
		{
			MessageBox(NULL, message.c_str(), "Info, just so you know!", MB_ICONINFORMATION);
		});
		info.detach();
	}
}

void dae::Logger::EnableInfoLogging()
{
	m_logInfo = true;
}

void dae::Logger::DisableInfoLogging()
{
	m_logInfo = false;
}

void dae::Logger::EnableInterupOnError()
{
	m_interuptOnError = true;
	LogInfo("Errors will interupt main program now!");
}

void dae::Logger::DisableInterupOnError()
{
	m_interuptOnError = false;
	LogInfo("Errors won't interupt main program now!");
}
