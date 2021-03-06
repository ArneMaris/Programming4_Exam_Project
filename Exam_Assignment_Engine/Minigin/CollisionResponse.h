#pragma once
#include "Response.h"

namespace dae
{
	class GameObject;
	class CollisionResponse : public Response
		{
		public:
			explicit CollisionResponse() = default;
			virtual ~CollisionResponse() = default;

			CollisionResponse(const CollisionResponse& other) = delete;
			CollisionResponse(CollisionResponse&& other) = delete;
			CollisionResponse& operator=(const CollisionResponse& other) = delete;
			CollisionResponse& operator=(CollisionResponse&& other) = delete;

			//may be called multiple times in a single frame
			virtual void OnCollisionStart(GameObject* otherObj) = 0;

			//may be called multiple times in a single frame
			virtual void OnCollisionEnd(GameObject* otherObj) = 0;

			// you dont have to do this, it will be automatically done when you add it on a component (gameobject of that component)
			// this is just here in case you need to change it runtime (probably never)
			void SetOwnerObject(GameObject* newOwner) { m_pOwnerObject = newOwner; };

		protected:
			GameObject* m_pOwnerObject = nullptr;
	};
}

