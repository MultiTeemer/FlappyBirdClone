#pragma once

#include "Obstacle.hpp"
#include "ObstaclesManager.hpp"

#include <list>
#include <Box2D.h>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

namespace FlappyBirdClone
{
	struct GameWorld
	{
		static const float PlayerSpeed;

		b2World world;
		b2Body* topBorder;
		b2Body* bottomBorder;
		std::list<Obstacle> obstacles;
		sf::Vector2u size;
		unsigned origin;

		struct Player
		{
			b2Body* body;
			b2Vec2 prevPos;
		} player;

		struct Progress
		{
			unsigned score;
			float distance;
		} progress;

		ObstaclesManager obstaclesManager;

		GameWorld();
		void Initialize(sf::RenderWindow& window);
		void Render(sf::RenderWindow& window);
		b2Body* createBox(int pos_x, int pos_y, int size_x, int size_y, b2BodyType type = b2_staticBody);

	private:
		void RenderBoundaries(sf::RenderWindow& window);
		void RenderObstacles(sf::RenderWindow& window);
		void RenderPlayer(sf::RenderWindow& window);

		void RenderBody(b2Body* body, sf::RenderWindow& window, sf::Vector2f shift = sf::Vector2f());
	};
}
