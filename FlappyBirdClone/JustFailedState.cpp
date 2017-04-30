#include "GameScreen.hpp"

namespace FlappyBirdClone
{
	GameScreen::JustFailedState::JustFailedState(GameScreen& screen)
		:
		State(screen)
	{}

	void GameScreen::JustFailedState::Update(float delta)
	{
		screen.SetState<FailedState>();
	}

	void GameScreen::JustFailedState::ProcessEvent(sf::Event& event) {}

	void GameScreen::JustFailedState::OnSet() {}
}