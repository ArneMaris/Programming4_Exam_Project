#include "MiniginPCH.h"
#include "Response.h"

dae::Response::Response()
	:m_ResponseID{ GameInfo::amountOfResponses }
{
	GameInfo::amountOfResponses++;
}

dae::Response::~Response()
{
	m_pObservers.clear();
}

void dae::Response::AddObserver(Observer* observer)
{
	m_pObservers.push_back(observer);
}

void dae::Response::RemoveObserver(Observer * observer)
{
	auto it = std::find(m_pObservers.begin(), m_pObservers.end(), observer);
	if (it != m_pObservers.end())
	{
		delete *it;
		*it = nullptr;
		it = m_pObservers.erase(it);
	}
	else
	{
		Logger::GetInstance().LogWarning(L"Trying to remove a non existing shape!");
	}
}

void dae::Response::Notify(const NotifyEvent& notifyEvent)
{
	for (auto obs : m_pObservers)
	{
		obs->OnNotify(notifyEvent, m_ResponseID);
	}
}

