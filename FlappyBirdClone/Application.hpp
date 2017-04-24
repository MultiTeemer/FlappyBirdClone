#pragma once

#include "Screen.hpp"

#include <memory>
#include <SFML\Graphics.hpp>
#include <SFGUI\SFGUI.hpp>

namespace FlappyBirdClone
{
	class Application
	{
	private:
		sf::RenderWindow window;
		sfg::SFGUI gui;

		static std::unique_ptr<Application> Instance;

		Application();

		void Update(float delta);
		void Render();
		void ProcessEvents();
	public:
		template <typename ScreenT, typename ...Args>
		std::shared_ptr<ScreenT> Create(Args&&... args)
		{
			auto* screen = new ScreenT(std::forward<Args>(args)...);
			screen->InitGui(window);
			return std::static_pointer_cast<ScreenT>(Screen::Screens.back());
		}

		static void Run(int fps);
	};
}