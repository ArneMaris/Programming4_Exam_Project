#include "MiniginPCH.h"
#include "GameInfo.h"

float dae::GameInfo::deltaTime = 0;
float dae::GameInfo::fixedTime = 0.016f;// 16 milliseconds = 60 fps,  32 milliseconds = 30fps
int dae::GameInfo::windowWidth = 640;
int dae::GameInfo::windowHeight = 480;

// increasing these increases the accuracy of your physics but also the computing time!
int dae::GameInfo::physicsVelocityIterations = 6; 
int dae::GameInfo::physicsPositionIterations = 3;