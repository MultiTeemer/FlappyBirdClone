#pragma once

#include <Box2D.h>

namespace FlappyBirdClone
{
	struct Player
	{
		b2Body* body;
		b2Vec2 prevPos;
	};
}
