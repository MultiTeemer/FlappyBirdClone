#pragma once

#include <Box2D.h>

namespace FlappyBirdClone
{
	struct Obstacle
	{
		static const int Width = 50;
		static const int PassageHeight = 210;

		b2Body* topBody = nullptr;
		b2Body* bottomBody = nullptr;
		
		float position = 0;
		float passage = 0;

		bool passed = false;

		bool Cover(float pos) const;
	};
}
