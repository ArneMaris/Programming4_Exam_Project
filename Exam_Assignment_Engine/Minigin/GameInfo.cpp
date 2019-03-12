#include "MiniginPCH.h"
#include "GameInfo.h"

float dae::GameInfo::deltaTime;
float dae::GameInfo::fixedTime;

dae::GameInfo::GameInfo()
{
	deltaTime = 0;
	fixedTime = 0.016f; // 16 milliseconds = 60 fps,  32 milliseconds = 30fps
}
