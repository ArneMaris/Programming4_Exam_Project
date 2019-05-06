#pragma once
#include "Box2D/Dynamics/b2WorldCallbacks.h"

namespace dae
{
	class MMCallbacks : public b2ContactListener
	{
	public:
		MMCallbacks();
		~MMCallbacks();

		virtual void BeginContact(b2Contact* contact);
		virtual void EndContact(b2Contact* contact);

	private:
		void HandleContact(b2Contact* contact, bool begin);
	};

}
