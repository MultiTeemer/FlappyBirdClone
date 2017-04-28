#pragma once

#include "Screen.hpp"
#include "Player.hpp"

#include <vector>
#include <Box2D.h>
#include <SFML\Graphics.hpp>

namespace FlappyBirdClone
{
	class GameScreen : Screen
	{
	public:
		virtual void Update(float delta);
		virtual void Render(sf::RenderWindow& window);
		virtual void InitGui(sf::RenderWindow& window);
		virtual void ProcessEvent(sf::Event& event, sf::RenderWindow& window);

		GameScreen();

	private:
		b2World world;
		std::vector<b2Body*> bodies;
		Player player;
		b2Vec2 prevPos;
		
		b2Body* createBox(b2World& world, int pos_x, int pos_y, int size_x, int size_y, b2BodyType type = b2_dynamicBody);
	};
}
