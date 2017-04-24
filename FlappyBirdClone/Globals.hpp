#pragma once

#include "Application.hpp"

namespace FlappyBirdClone
{
	struct Globals
	{
		static Application* App;

		Globals() = delete;
		Globals(const Globals&) = delete;
	};
}