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

		Response(const Response& other) = delete;
		Response(Response&& other) = delete;
		Response& operator=(const Response& other) = delete;
		Response& operator=(Response&& other) = delete;

		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);
		void Notify(const NotifyEvent& notifyEvent);

		void DontDoTransitionNow() { m_MayTranstion = false; };
		bool MayDoTransition()
		{
			if (m_MayTranstion)
			{
				return true;
			}
			else
			{
				m_MayTranstion = true;
				return false;
			}
		};

		const int GetResponseID() const { return m_ResponseID; };
	private:
		std::vector<std::shared_ptr<Observer>> m_pObservers;
		const int m_ResponseID;
		bool m_MayTranstion = true;
	};
}
