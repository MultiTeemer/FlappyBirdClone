#include "GameScreen.hpp"

#include <Box2D.h>

namespace FlappyBirdClone
{
	GameScreen::GameScreen()
		:
		currentState(nullptr)
	{}

	void GameScreen::Update(float delta)
	{
		Screen::Update(delta);

		currentState->Update(delta);
	}

	void GameScreen::Render(sf::RenderWindow& window)
	{
		Screen::Render(window);

		gameWorld.Render(window);
	}

	void GameScreen::Initialize(sf::RenderWindow& window)
	{
		Screen::Initialize(window);

		gameWorld.Initialize(window);

		InitializeGui(window);
	
		SetState<PlayingState>();
	}

	void GameScreen::ProcessEvent(sf::Event& event, sf::RenderWindow& window)
	{
		Screen::ProcessEvent(event, window);

		currentState->ProcessEvent(event);
	}

	void GameScreen::InitializeGui(sf::RenderWindow& window)
	{
		auto scoreLabel = Ui.Add<sfg::Label>(scoreLabelId, std::to_string(gameWorld.progress.score));
		scoreLabel->SetPosition(sf::Vector2f(5, 5));

		const auto windowCenter = window.getDefaultView().getCenter();

		auto gamePausedLabel = Ui.Add<sfg::Label>(gamePausedLabelId, "PAUSED");
		gamePausedLabel->SetPosition(windowCenter);
		
		const int boxWidth = 400;
		const int boxHeight = 300;

		auto recapWindow = Ui.Add<sfg::Window>(recapWindowId);
		recapWindow->SetTitle("Game Over");
		recapWindow->SetPosition(sf::Vector2f(windowCenter.x - boxWidth / 2, windowCenter.y - boxHeight / 2));

		auto recapScoreLabel = Ui.Create<sfg::Label>("Your score:");
		auto recapScore = Ui.Add<sfg::Label>(recapScoreLabelId);
		auto b1 = Ui.Wrap({ recapScoreLabel, recapScore }, sfg::Box::Orientation::HORIZONTAL);

		auto bestScoreLabel = Ui.Create<sfg::Label>("Best score:");
		auto bestScore = Ui.Add<sfg::Label>(bestScoreLabelId);
		auto b2 = Ui.Wrap({ bestScoreLabel, bestScore }, sfg::Box::Orientation::HORIZONTAL);

		auto toMainMenuButton = Ui.Add<sfg::Button>(toMainMenuButtonId, "Main Menu");
		toMainMenuButton->GetSignal(sfg::Button::OnLeftClick).Connect([this] { this->ReturnToMainMenu(); });

		auto recapBox = Ui.Wrap({ b1, b2, toMainMenuButton }, sfg::Box::Orientation::VERTICAL, 15);

		recapBox->SetRequisition(sf::Vector2f(boxWidth, boxHeight));

		recapWindow->Add(recapBox);
	}

	void GameScreen::ReturnToMainMenu()
	{
		Globals::App->Create<MainMenuScreen>();
		Close();
	}

	
}