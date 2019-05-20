#pragma once
#include "Box2D/Dynamics/b2WorldCallbacks.h"
class b2Contact;

namespace dae
{
	class CollisionCallbacks : public b2ContactListener
	{
	public:
		CollisionCallbacks() = default;
		~CollisionCallbacks() = default;

		CollisionCallbacks(const CollisionCallbacks& other) = delete;
		CollisionCallbacks(CollisionCallbacks&& other) noexcept = delete;
		CollisionCallbacks& operator=(const CollisionCallbacks& other) = delete;
		CollisionCallbacks& operator=(CollisionCallbacks&& other) noexcept = delete;

		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;

	private:
		void HandleContact(b2Contact* contact, bool begin);
	};

}
