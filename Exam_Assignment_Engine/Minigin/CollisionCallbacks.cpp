#include "MiniginPCH.h"
#include "CollisionCallbacks.h"
#include "GameObject.h"
#include "ColliderComponent.h"

void dae::CollisionCallbacks::BeginContact(b2Contact* contact)
{
	HandleContact(contact, true);
}

void dae::CollisionCallbacks::EndContact(b2Contact* contact)
{
	HandleContact(contact, false);
}

void dae::CollisionCallbacks::HandleContact(b2Contact * contact, bool begin)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
	GameObject* obj1 = nullptr;
	GameObject* obj2 = nullptr;
	if (bodyUserData)
		obj1 = static_cast<GameObject*>(bodyUserData);
	if (bodyUserData2)
		obj2 = static_cast<GameObject*>(bodyUserData2);

		if (obj1 != nullptr && obj2 != nullptr && obj1->GetComponent<ColliderComponent>() && obj2->GetComponent<ColliderComponent>())
		{
			if (begin)
			{
				obj2->GetComponent<ColliderComponent>()->StartCollisionWith(obj1);
				obj1->GetComponent<ColliderComponent>()->StartCollisionWith(obj2);
			}
			else
			{
				obj2->GetComponent<ColliderComponent>()->EndCollisionWith(obj1);
				obj1->GetComponent<ColliderComponent>()->EndCollisionWith(obj2);
			}
		}
}
