#include "MiniginPCH.h"
#include "CommandExample.h"

void CommandExample::ExecuteOnPress()
{

}

void CommandExample::ExecuteOnHold(const b2Vec2& axisValues)
{
	UNREFERENCED_PARAMETER(axisValues);
	dae::Logger::GetInstance().LogInfo(L"HOLDING :D");
}

void CommandExample::ExecuteOnRelease()
{

}
