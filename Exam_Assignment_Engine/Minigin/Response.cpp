#include "MiniginPCH.h"
#include "Response.h"

dae::Response::~Response()
{
	for (auto obs : m_pObservers)
	{
		delete obs;
	}
	m_pObservers.clear();
}

void dae::Response::AddObserver(Observer* observer)
{
	if (std::find_if(m_pObservers.begin(), m_pObservers.end(),
		[observer](Observer* obs) {return typeid(observer) == typeid(obs); }) == m_pObservers.end())
	{
		m_pObservers.push_back(observer);
	}
	else
	{
		Logger::GetInstance().LogWarning(L"Already added this observer, call ignored!");
	}
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
		obs->OnNotify(notifyEvent, this);
	}
}

