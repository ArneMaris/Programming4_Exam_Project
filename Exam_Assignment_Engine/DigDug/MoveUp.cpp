#include "pch.h"
#include "MoveUp.h"

void MoveUp::ExecuteOnPress()
{

}

void MoveUp::ExecuteOnHold(const b2Vec2 axisValues)
{
	UNREFERENCED_PARAMETER(axisValues);
	dae::Logger::GetInstance().LogInfo(L"HOLDING w");
}

void MoveUp::ExecuteOnRelease()
{

}
