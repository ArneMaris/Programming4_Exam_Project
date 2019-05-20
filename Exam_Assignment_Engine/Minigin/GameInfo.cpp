#include "MiniginPCH.h"
#include "GameInfo.h"

float dae::GameInfo::deltaTime = 0; //dont touch this, will be updated automatically, you can acces it to make movement etc framerate independent

//timestep by wich physics will step, the lower the better accuracy your physics will have (Better don't go 0.016 = 16ms!)
float dae::GameInfo::fixedTime = 0.016f;// 16 milliseconds = 60 fps,  32 milliseconds = 30fps

int dae::GameInfo::windowWidth = 1280;
int dae::GameInfo::windowHeight = 720;

// increasing these increases the accuracy of your physics but also the computing time!
int dae::GameInfo::physicsVelocityIterations = 6; 
int dae::GameInfo::physicsPositionIterations = 3;

bool dae::GameInfo::enableVsync = false;

bool dae::GameInfo::drawPhysicsDebug = false; //this is the default value, can be changed during runtime

int dae::GameInfo::amountOfGameObjects = 0; //just a counter to keep track of gameObject amount
int dae::GameInfo::amountOfResponses = 0; //just a counter to keep track of Responses amount

bool dae::GameInfo::gameEnded = false;