#include "MiniginPCH.h"
#include "MMCallbacks.h"
#include "GameObject.h"
#include "ColliderComponent.h"

dae::MMCallbacks::MMCallbacks()
{
}


dae::MMCallbacks::~MMCallbacks()
{
}

inline void dae::MMCallbacks::BeginContact(b2Contact* contact)
{
	HandleContact(contact, true);
}

inline void dae::MMCallbacks::EndContact(b2Contact* contact)
{
	HandleContact(contact, false);
}

void dae::MMCallbacks::HandleContact(b2Contact * contact, bool begin)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
	GameObject* obj1 = nullptr;
	GameObject* obj2 = nullptr;
	if (bodyUserData)
		obj1 = static_cast<GameObject*>(bodyUserData);
	if (bodyUserData2)
		obj2 = static_cast<GameObject*>(bodyUserData2);

		if (obj1 != nullptr && obj2 != nullptr)
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
