#pragma once

#include "Application.hpp"

namespace FlappyBirdClone
{
	struct Globals
	{
		static Application* App;
		static unsigned BestScore;

		Globals() = delete;
		Globals(const Globals&) = delete;
	};
}