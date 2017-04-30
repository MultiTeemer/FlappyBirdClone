#pragma once

#include "Application.hpp"

namespace FlappyBirdClone
{
	struct Globals
	{
		static Application* App;
		static int BestScore;

		Globals() = delete;
		Globals(const Globals&) = delete;
	};
}