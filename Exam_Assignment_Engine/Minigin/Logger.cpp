#include "MiniginPCH.h"
#include "Logger.h"
#include <thread>

bool dae::Logger::m_logInfo{ false };
bool dae::Logger::m_interuptOnError{ false };

dae::Logger::Logger()
{

}

dae::Logger::~Logger()
{

}

void dae::Logger::LogWarning(const std::wstring& message)
{
	std::string str{ message.begin(), message.end() };
	std::thread warning([str]
		{
			MessageBox(NULL, str.c_str(), "Warning, be carefull!", MB_ICONWARNING);
		});
	warning.detach();
}

void dae::Logger::LogError(const std::wstring& message)
{
	std::string str{ message.begin(), message.end() };
	if (!m_interuptOnError)
	{
		std::thread error([str]
			{
				MessageBox(NULL,str.c_str(), "Error, you should shut down!", MB_ICONERROR);
			});
		error.detach();
	}
	else
	{
		MessageBox(NULL, str.c_str(), "Error, you should shut down!", MB_ICONERROR);
	}
}

void dae::Logger::LogInfo(const std::wstring& message)
{
	std::string str{ message.begin(), message.end() };
	if (m_logInfo)
	{
		std::thread info([str]
		{
			MessageBox(NULL, str.c_str(), "Info, just so you know!", MB_ICONINFORMATION);
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
	LogInfo(L"Errors will interupt main program now!");
}

void dae::Logger::DisableInterupOnError()
{
	m_interuptOnError = false;
	LogInfo(L"Errors won't interupt main program now!");
}
