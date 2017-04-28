#include "Application.hpp"

#include <memory>
#include <SFML\System\Time.hpp>
#include "Screen.hpp"
#include "MainMenuScreen.hpp"
#include "Globals.hpp"

namespace FlappyBirdClone
{
	std::vector<std::shared_ptr<Screen>> Screen::Screens = std::vector<std::shared_ptr<Screen>>();

	std::unique_ptr<Application> Application::Instance = std::unique_ptr<Application>();

	Application::Application()
		: window(sf::VideoMode(1024, 768), "Flappy bird", sf::Style::Default)
	{
		window.setVerticalSyncEnabled(true);
	}

	void Application::Run(int fps)
	{
		if (!Instance) {
			Instance = std::unique_ptr<Application>(new Application());
			Globals::App = Instance.get();
		} else {
			throw new std::logic_error("Application has been already run!");
		}

		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		const sf::Time updateAfter = sf::seconds(1.f / fps);

		Instance->Create<MainMenuScreen>();

		while (Instance->window.isOpen()) {
			Instance->ProcessEvents();

			timeSinceLastUpdate += clock.restart();
			if (timeSinceLastUpdate >= updateAfter) {
				Instance->Update(timeSinceLastUpdate.asSeconds());
				Instance->Render();

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}

	void Application::Update(float delta)
	{
		for (auto& s : Screen::Screens) {
			s->Update(delta);
		}
	}

	void Application::Render()
	{
		window.clear();

		for (auto& s : Screen::Screens) {
			s->Render(window);
			s->RenderGui(window, gui);
		}

		window.display();
	}

	void Application::ProcessEvents()
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		auto screens = Screen::Screens;
		for (auto& screen_ptr : screens) {
			screen_ptr->ProcessEvent(event, window);
		}
	}
}