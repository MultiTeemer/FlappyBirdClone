#include "GameScreen.hpp"

namespace FlappyBirdClone
{
	GameScreen::JustFailedState::JustFailedState(GameScreen& screen)
		:
		State(screen)
	{}

	void GameScreen::JustFailedState::Update(float delta)
	{
		const float zeroTolerance = 1e-6;

		screen.gameWorld.Update(delta);

		const auto b = screen.gameWorld.player.body;
		const auto isPlayerIdle = abs(b->GetAngularVelocity()) < zeroTolerance
			&& abs(b->GetLinearVelocity().Length()) < zeroTolerance;
		if (isPlayerIdle) {
			screen.SetState<FailedState>();
		}
	}

	void GameScreen::JustFailedState::ProcessEvent(sf::Event& event) {}

	void GameScreen::JustFailedState::OnSet()
	{
		screen.gameWorld.player.body->GetFixtureList()->SetDensity(5);
		screen.gameWorld.player.body->GetFixtureList()->SetFriction(1);

		screen.Ui.Get<sfg::Label>(GameScreen::scoreLabelId)->Show(true);

		screen.Ui.Get<sfg::Label>(GameScreen::gamePausedLabelId)->Show(false);
		screen.Ui.Get<sfg::Window>(GameScreen::recapWindowId)->Show(false);
	}
}