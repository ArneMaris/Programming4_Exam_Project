#include "pch.h"
#include "InputResponses.h"
#include "GameObject.h"
#include "Components.h"

void Move::ExecuteOnPress()
{
	dae::Logger::GetInstance().LogInfo(L"Stick start");
}
void Move::ExecuteOnHold(const b2Vec2 axisValues)
{
	UNREFERENCED_PARAMETER(axisValues);
	//dae::Logger::GetInstance().LogInfo(L"Stick being used");
	float angle = RadToDegrees(atan2f(axisValues.x, axisValues.y));
	if (abs(angle) > 135)
	{
		m_pOwnerObject->GetTransform()->Translate(0, -1);
	}
	else if (abs(angle) > 45)
	{
		if (angle > 0)
			m_pOwnerObject->GetTransform()->Translate(1, 0);
		else
			m_pOwnerObject->GetTransform()->Translate(-1, 0);
	}
	else
	{
		m_pOwnerObject->GetTransform()->Translate(0, 1);
	}
	//m_pOwnerObject->GetTransform()->SetRotation(DegreesToRad(angle));
	dae::Logger::GetInstance().LogInfo(std::to_wstring(angle));
	//m_pOwnerObject->GetTransform()->Translate(axisValues);
}
void Move::ExecuteOnRelease()
{
	dae::Logger::GetInstance().LogInfo(L"Stick end");
}

