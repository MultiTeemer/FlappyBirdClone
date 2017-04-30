#include "GameScreen.hpp"

namespace FlappyBirdClone
{
	GameScreen::State::State(GameScreen& screen)
		:
		screen(screen)
	{}

	void GameScreen::State::Update(float delta) {}

	void GameScreen::State::ProcessEvent(sf::Event& event) {}

	void GameScreen::State::OnSet() {}
}