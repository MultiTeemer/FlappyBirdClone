#pragma once

#include <SFML\Graphics.hpp>

namespace FlappyBirdClone
{
	struct GameWorld;

	class ObstaclesManager
	{
	public:
		ObstaclesManager(GameWorld& world);
		void Initialize();
		void Update();

	private:
		static const int OutOfScreenGap = 100;

		GameWorld& world;

		void ClearPassedObstacles();
		void EmitObstacle(float position, float passage);
		
		float EmitNewObstacles(float startFrom);
		float CalcDistanceToLastObstacle(float from) const;
		float CalcPassageForObstacle(float obstaclePosition) const;
		
		int CalcObstaclesCountInChunk(float startFrom) const;
		
		bool MayBeEmitObstacle(float position) const;
	};
}
