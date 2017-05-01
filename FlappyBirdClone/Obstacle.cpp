#include "Obstacle.hpp"

namespace FlappyBirdClone
{
	bool Obstacle::Cover(float point) const
	{
		return point >= position - Width / 2 && point <= position + Width / 2;
	}
}