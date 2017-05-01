#include "GameScreen.hpp"

namespace FlappyBirdClone
{
	GameScreen::FailedState::FailedState(GameScreen& screen)
		:
		State(screen)
	{}

	void GameScreen::FailedState::Update(float delta) {}

	void GameScreen::FailedState::ProcessEvent(sf::Event& event)
	{
		screen.Ui.Get<sfg::Window>(GameScreen::recapWindowId)->HandleEvent(event);
	}

	void GameScreen::FailedState::OnSet()
	{
		screen.Ui.Get<sfg::Window>(GameScreen::recapWindowId)->Show(true);
		screen.Ui.Get<sfg::Label>(GameScreen::recapScoreLabelId)->SetText(std::to_string(screen.gameWorld.progress.score));
		screen.Ui.Get<sfg::Label>(GameScreen::bestScoreLabelId)->SetText(std::to_string(Globals::BestScore));

		screen.Ui.Get<sfg::Label>(GameScreen::gamePausedLabelId)->Show(false);
		screen.Ui.Get<sfg::Label>(GameScreen::scoreLabelId)->Show(false);

		Globals::BestScore = std::max(Globals::BestScore, screen.gameWorld.progress.score);
	}
}