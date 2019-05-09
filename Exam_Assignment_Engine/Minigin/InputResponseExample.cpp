#include "MiniginPCH.h"
#include "InputResponseExample.h"

void InputResponseExample::ExecuteOnPress()
{

}

void InputResponseExample::ExecuteOnHold(const b2Vec2 axisValues)
{
	UNREFERENCED_PARAMETER(axisValues);
	dae::Logger::GetInstance().LogInfo(L"HOLDING w");
}

void InputResponseExample::ExecuteOnRelease()
{

}
