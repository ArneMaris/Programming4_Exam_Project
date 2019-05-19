#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "targetver.h"

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>
#include <algorithm>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma comment(lib,"xinput.lib")

#include "Logger.h" // Various logging functions
#include "GameInfo.h"

#include "Box2D.h" //physics, vectors, etc
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include <SDL.h>

#include "Utility.h"
