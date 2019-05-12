#pragma once
#include <vector>
#include "Logger.h"
#include "Observer.h"


namespace dae
{
	class Response
	{
	public:
		Response() = default;
		virtual ~Response();

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(const NotifyEvent& notifyEvent);
	private:
		std::vector<Observer*> m_pObservers;
	};
}
