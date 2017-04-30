#include "GameScreen.hpp"

namespace FlappyBirdClone
{
	GameScreen::PausedState::PausedState(GameScreen& screen)
		:
		State(screen)
	{
		screen.data.player.body->SetAngularVelocity(0);
		screen.data.player.body->SetLinearVelocity(b2Vec2_zero);
	}

	void GameScreen::PausedState::Update(float delta)
	{
		
	}

	void GameScreen::PausedState::ProcessEvent(sf::Event& event)
	{
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape) {
			screen.SetState<PlayingState>();
		}
	}

	void GameScreen::PausedState::OnSet()
	{
		screen.Ui.Get<sfg::Label>(GameScreen::gamePausedLabelId)->Show(true);

		screen.Ui.Get<sfg::Window>(GameScreen::recapWindowId)->Show(false);
		screen.Ui.Get<sfg::Label>(GameScreen::scoreLabelId)->Show(false);
	}
}