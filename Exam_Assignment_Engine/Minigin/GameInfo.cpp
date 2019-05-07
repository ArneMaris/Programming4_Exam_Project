#include "MiniginPCH.h"
#include "GameInfo.h"

float dae::GameInfo::deltaTime = 0;
float dae::GameInfo::fixedTime = 0.016f;// 16 milliseconds = 60 fps,  32 milliseconds = 30fps
const int dae::GameInfo::windowWidth = 1280;
const int dae::GameInfo::windowHeight = 720;

// increasing these increases the accuracy of your physics but also the computing time!
int dae::GameInfo::physicsVelocityIterations = 6; 
int dae::GameInfo::physicsPositionIterations = 3;

bool dae::GameInfo::enableVsync = false;

bool dae::GameInfo::drawPhysicsDebug = false;

int dae::GameInfo::amountOfGameObjects = 0;