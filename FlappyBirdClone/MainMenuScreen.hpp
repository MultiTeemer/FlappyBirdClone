#pragma once

#include "Screen.hpp"

#include <SFGUI/Widgets.hpp>

#include <memory>

namespace FlappyBirdClone
{
	class MainMenuScreen : public Screen
	{
	private:
		const int playButtonId = 0;

		void StartGame();
	public:
		virtual void Initialize(sf::RenderWindow& window);
		virtual void Update(float delta);
		virtual void Render(sf::RenderWindow& window);
		virtual void ProcessEvent(sf::Event& event, sf::RenderWindow& window);
	};
}