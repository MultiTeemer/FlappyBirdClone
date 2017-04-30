#include "GameScreen.hpp"

#include "Box2dConverter.hpp"

#include <Box2D.h>

namespace FlappyBirdClone
{
	GameScreen::GameScreen()
		:
		data{ b2Vec2(0, 9.8f) },
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

		for (b2Body* body = data.world.GetBodyList(); body != nullptr; body = body->GetNext()) {
			auto shape = static_cast<sf::Shape*>(body->GetUserData());
			shape->setPosition(Converter::MetersToPixels(body->GetPosition().x), Converter::MetersToPixels(body->GetPosition().y));
			shape->setRotation(Converter::RadToDeg<double>(body->GetAngle()));
			window.draw(*shape);
		}
	}

	void GameScreen::Initialize(sf::RenderWindow& window)
	{
		Screen::Initialize(window);

		InitializeGui(window);
		InitializeWorld(window);		
	
		SetState<PlayingState>();
	}

	void GameScreen::ProcessEvent(sf::Event& event, sf::RenderWindow& window)
	{
		Screen::ProcessEvent(event, window);

		currentState->ProcessEvent(event);
	}

	void GameScreen::InitializeGui(sf::RenderWindow& window)
	{
		auto scoreLabel = Ui.Add<sfg::Label>(scoreLabelId, std::to_string(data.score));
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

	void GameScreen::InitializeWorld(sf::RenderWindow& window)
	{
		data.bottomBorder = createBox(
			data.world,
			window.getSize().x / 2,
			window.getSize().y,
			8000,
			40,
			b2BodyType::b2_staticBody
		);
		data.topBorder = createBox(
			data.world,
			window.getSize().x / 2,
			20,
			8000,
			40,
			b2BodyType::b2_staticBody
		);

		data.player.body = createBox(
			data.world,
			window.getSize().x / 3,
			window.getSize().y / 2,
			60,
			40,
			b2BodyType::b2_dynamicBody
		);

		data.bodies.push_back(data.player.body);
	}

	void GameScreen::ReturnToMainMenu()
	{
		Globals::App->Create<MainMenuScreen>();
		Close();
	}

	b2Body* GameScreen::createBox(b2World& world, int pos_x, int pos_y, int size_x, int size_y, b2BodyType type)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(Converter::PixelsToMeters<double>(pos_x),
			Converter::PixelsToMeters<double>(pos_y));
		bodyDef.type = type;
		b2PolygonShape b2shape;
		b2shape.SetAsBox(Converter::PixelsToMeters<double>(size_x / 2.0),
			Converter::PixelsToMeters<double>(size_y / 2.0));
		b2FixtureDef fixtureDef;
		fixtureDef.density = 7;
		fixtureDef.friction = 1;
		fixtureDef.restitution = 0.01;
		fixtureDef.shape = &b2shape;
		b2Body* res = world.CreateBody(&bodyDef);
		res->CreateFixture(&fixtureDef);
		sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(size_x, size_y));
		shape->setOrigin(size_x / 2.0, size_y / 2.0);
		shape->setPosition(sf::Vector2f(pos_x, pos_y));
		if (type == b2_dynamicBody)
			shape->setFillColor(sf::Color::Blue);
		else
			shape->setFillColor(sf::Color::White);
		res->SetUserData(shape);
		return res;
	}
}