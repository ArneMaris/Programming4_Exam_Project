#pragma once
#include "MiniginPCH.h"
/*=============================================================================*/
// Copyright 2017-2018 Elite Engine
// Authors: Matthieu Delaere
/*=============================================================================*/
//FROM GAMEPLAY PROGRAMMING 2019

namespace dae
{
		//Manhattan distance
		static float Manhattan(float x, float y)
		{
			return float(x + y);
		}

		//Euclidean distance
		static float Euclidean(float x, float y)
		{
			return float(sqrt(x*x + y * y));
		}

		//Sqrt Euclidean distance
		static float SqrtEuclidean(float x, float y)
		{
			return float(x*x + y * y);
		}

		//Octile distance
		static float Octile(float x, float y)
		{
			auto f = 0.414213562373095048801f; // == sqrt(2) - 1;
			return float((x < y) ? f * x + y : f * y + x);
		}
}