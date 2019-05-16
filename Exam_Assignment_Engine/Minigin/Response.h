#pragma once
#include <vector>
#include "Logger.h"
#include "Observer.h"


namespace dae
{
	class Response
	{
	public:
		Response();
		virtual ~Response();

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(const NotifyEvent& notifyEvent);

		const int GetResponseID() const { return m_ResponseID; };
	private:
		std::vector<std::shared_ptr<Observer>> m_pObservers;
		const int m_ResponseID;
	};
}
