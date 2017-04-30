#pragma once

#include "Ui.h"
#include <vector>
#include <memory>
#include <functional>
#include <SFML\Graphics.hpp>
#include <SFGUI\SFGUI.hpp>

namespace FlappyBirdClone
{
	class Screen
	{
	private:
		friend class Application;

		static std::vector<std::shared_ptr<Screen>> Screens;

		void RenderGui(sf::RenderWindow& window, sfg::SFGUI& gui)
		{
			window.resetGLStates();
			gui.Display(window);
		}

		void SelfRemoveFromActiveScreens()
		{
			auto it = std::find_if(Screens.begin(), Screens.end(), [this](const std::shared_ptr<Screen>& ptr) -> bool {
				return ptr.get() == this;
			});
			if (it != Screens.end()) {
				Screens.erase(it);
			}
		}

	protected:
		Ui Ui;

		Screen()
		{
			Screens.push_back(std::shared_ptr<Screen>(this));
		}

	public:
		virtual ~Screen()
		{
			SelfRemoveFromActiveScreens();
		}

		virtual void Close()
		{
			SelfRemoveFromActiveScreens();
		}
		
		virtual void Render(sf::RenderWindow& window) {}
		virtual void Initialize(sf::RenderWindow& window) {}

		virtual void Update(float delta)
		{
			Ui.Update(delta);
		}
		
		virtual void ProcessEvent(sf::Event& event, sf::RenderWindow& window)
		{
			Ui.ProcessEvent(event);
		}
	};
}
