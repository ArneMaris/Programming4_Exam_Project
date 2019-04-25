#pragma once

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

#include "Logger.h" // Various logging functions
#include "GameInfo.h"

#include "Box2D.h" //physics, vectors, etc
#include "imgui.h"
#include "imgui_impl_sdl.h"
