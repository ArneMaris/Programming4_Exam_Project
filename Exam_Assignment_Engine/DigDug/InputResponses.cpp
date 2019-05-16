#include "pch.h"
#include "InputResponses.h"

void Move::ExecuteOnPress()
{
	dae::Logger::GetInstance().LogInfo(L"Stick start");
}
void Move::ExecuteOnHold(const b2Vec2 axisValues)
{
	UNREFERENCED_PARAMETER(axisValues);
	dae::Logger::GetInstance().LogInfo(L"Stick being used");
}
void Move::ExecuteOnRelease()
{
	dae::Logger::GetInstance().LogInfo(L"Stick end");
}

