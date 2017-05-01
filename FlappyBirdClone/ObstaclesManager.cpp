#include "ObstaclesManager.hpp"

#include "GameWorld.h"
#include "RangeMapper.hpp"
#include "Utils.hpp"

#include <algorithm>
#include <map>
#include <limits>

namespace FlappyBirdClone
{
	ObstaclesManager::ObstaclesManager(GameWorld& world)
		:
		world(world)
	{}

	void ObstaclesManager::Initialize()
	{
		const auto worldWidth = world.size.x;

		for (float p = worldWidth / 2; p < worldWidth + OutOfScreenGap; p += 5) {
			if (MayBeEmitObstacle(p)) {
				auto chunkEndPos = EmitNewObstacles(p);

				p = chunkEndPos;
			}
		}
	}

	void ObstaclesManager::Update()
	{
		ClearPassedObstacles();

		const auto pos = world.progress.distance + world.size.x + OutOfScreenGap;
		if (MayBeEmitObstacle(pos)) {
			EmitNewObstacles(pos);
		}
	}

	void ObstaclesManager::ClearPassedObstacles()
	{
		while (!world.obstacles.empty() && world.progress.distance - world.obstacles.front().position > world.size.x / 2) {
			world.world.DestroyBody(world.obstacles.front().topBody);
			world.world.DestroyBody(world.obstacles.front().bottomBody);
			world.obstacles.pop_front();
		}
	}

	float ObstaclesManager::EmitNewObstacles(float startFrom)
	{
		const auto firstObstaclePlace = startFrom + Obstacle::Width / 2.f;
		const auto count = CalcObstaclesCountInChunk(startFrom);

		float pos = firstObstaclePlace;

		for (int i = 0; i < count; ++i) {
			const auto passage = CalcPassageForObstacle(pos);
			EmitObstacle(pos, passage);

			pos += Obstacle::Width / 2;

			if (i != count - 1) {
				pos += Utils::GetRandom<float>(100, 500);
			}
		}

		return pos;
	}

	bool ObstaclesManager::MayBeEmitObstacle(float position) const
	{
		const auto clearZone = Obstacle::Width / 2.f + 300;
		const auto distanceToLastObstacle = CalcDistanceToLastObstacle(position);

		if (distanceToLastObstacle < 0 || distanceToLastObstacle <= clearZone) {
			return false;
		} else {
			RangeMapper distanceToLastObstacleFactor;
			distanceToLastObstacleFactor[clearZone + 300] = 0.25f;
			distanceToLastObstacleFactor[500] = 0.50f;
			distanceToLastObstacleFactor[std::numeric_limits<float>::infinity()] = 1.f;

			RangeMapper positionFactor;
			positionFactor[800] = 0.1f;
			positionFactor[1800] = 0.2f;
			positionFactor[3000] = 0.33f;
			positionFactor[6000] = 0.45f;
			positionFactor[8000] = 0.7f;
			positionFactor[std::numeric_limits<float>::infinity()] = 0.85f;

			float dice = rand() / (float)RAND_MAX;
			float p = distanceToLastObstacleFactor(distanceToLastObstacle) + positionFactor(position);

			return dice < p;
		}
	}

	void ObstaclesManager::EmitObstacle(float position, float passage)
	{
		Obstacle obstacle;
		obstacle.position = position;
		obstacle.passage = passage;
		
		const auto topObstaclePartHeight = passage - Obstacle::PassageHeight / 2;
		obstacle.topBody = world.createBox(position, topObstaclePartHeight / 2, Obstacle::Width, topObstaclePartHeight);

		const auto bottomObstaclePartHeight = world.size.y - passage - Obstacle::PassageHeight / 2;
		obstacle.bottomBody = world.createBox(position, world.size.y - bottomObstaclePartHeight / 2, Obstacle::Width, bottomObstaclePartHeight);

		world.obstacles.push_back(obstacle);
	}

	float ObstaclesManager::CalcDistanceToLastObstacle(float from) const
	{
		return world.obstacles.size() > 0 ? from - world.obstacles.back().position : std::numeric_limits<float>::max();
	}

	float ObstaclesManager::CalcPassageForObstacle(float obstaclePosition) const
	{
		const auto distanceToLastObstacle = CalcDistanceToLastObstacle(obstaclePosition);
		const auto lastObstaclePassage = world.obstacles.empty() ? world.size.y / 2 : world.obstacles.back().passage;
		const auto maxPassageDispersion = world.size.y - Obstacle::PassageHeight;

		RangeMapper lastObstaclePassageWeight;
		lastObstaclePassageWeight[Obstacle::Width] = 1.f;
		lastObstaclePassageWeight[Obstacle::Width * 2] = 0.5f;
		lastObstaclePassageWeight[200] = 0.4f;
		lastObstaclePassageWeight[300] = 0.3f;
		lastObstaclePassageWeight[500] = 0.1f;
		lastObstaclePassageWeight[std::numeric_limits<float>::infinity()] = 0;

		const auto dispersion = maxPassageDispersion * (1 - lastObstaclePassageWeight(distanceToLastObstacle));

		return Utils::Clamp<float>(
			Utils::GetRandom(
				lastObstaclePassage - dispersion,
				lastObstaclePassage + dispersion
			),
			Obstacle::PassageHeight / 2.f,
			world.size.y - Obstacle::PassageHeight / 2.f
		);
	}

	int ObstaclesManager::CalcObstaclesCountInChunk(float startFrom) const
	{
		RangeMapper minDistanceFactor;
		minDistanceFactor[500] = 1;
		minDistanceFactor[1000] = 3;
		minDistanceFactor[2500] = 5;
		minDistanceFactor[5000] = 7;
		minDistanceFactor[std::numeric_limits<float>::infinity()] = 9;

		RangeMapper maxDistanceFactor;
		maxDistanceFactor[500] = 3;
		maxDistanceFactor[1000] = 6;
		maxDistanceFactor[2500] = 9;
		maxDistanceFactor[5000] = 16;
		maxDistanceFactor[std::numeric_limits<float>::infinity()] = 20;

		const auto minCount = minDistanceFactor(startFrom);
		const auto maxCount = maxDistanceFactor(startFrom);

		return Utils::GetRandom(minCount, maxCount);
	}
}