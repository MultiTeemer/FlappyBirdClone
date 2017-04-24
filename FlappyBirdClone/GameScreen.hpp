#pragma once

#include "Screen.hpp"

#include <SFML\Graphics.hpp>

namespace FlappyBirdClone
{
	class GameScreen : Screen
	{
	public:
		virtual void Update(float delta);
		virtual void Render(sf::RenderWindow& window);
		virtual void InitGui();
		virtual void ProcessEvent(sf::Event& event);
	};
}
