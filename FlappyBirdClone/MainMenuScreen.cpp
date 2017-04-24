#include "MainMenuScreen.hpp"

#include <SFGUI\Widgets.hpp>

namespace FlappyBirdClone
{
	void MainMenuScreen::InitGui(sf::RenderWindow& window)
	{
		Screen::InitGui(window);

		auto startGameBtn = Ui.Add<sfg::Button>(playButtonId, "Play");
		auto screenSize = window.getSize();
		startGameBtn->SetPosition(sf::Vector2f(screenSize.x / 2, screenSize.y / 2));
		startGameBtn->GetSignal(sfg::Widget::OnLeftClick).Connect([this]() {
			this->StartGame();
		});
	}

	void MainMenuScreen::Update(float delta)
	{
		Screen::Update(delta);
	}

	void MainMenuScreen::ProcessEvent(sf::Event& event)
	{
		Screen::ProcessEvent(event);
	}

	void MainMenuScreen::Render(sf::RenderWindow& window)
	{
		
	}

	void MainMenuScreen::StartGame()
	{

	}
}