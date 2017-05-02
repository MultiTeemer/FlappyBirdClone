#include "GameWorld.h"

#include "Box2dConverter.hpp"

namespace FlappyBirdClone
{
	const float GameWorld::PlayerSpeed = 150.f;

	GameWorld::GameWorld()
		:
		world(b2Vec2(0, 9.8f)),
		topBorder(nullptr),
		bottomBorder(nullptr),
		player{nullptr, b2Vec2_zero},
		progress{0, 0},
		obstaclesManager(*this)
	{}

	void GameWorld::Initialize(sf::RenderWindow& window)
	{
		size = window.getSize();
		origin = size.x / 3;

		bottomBorder = createBox(
			size.x / 2,
			size.y,
			size.x * 2,
			40
		);
		topBorder = createBox(
			size.x / 2,
			20,
			size.x * 2,
			40
		);

		player.body = createBox(
			0,
			size.y / 2,
			40,
			35,
			b2BodyType::b2_dynamicBody
		);

		obstaclesManager.Initialize();
	}

	void GameWorld::Render(sf::RenderWindow& window)
	{
		RenderBoundaries(window);
		RenderObstacles(window);
		RenderPlayer(window);
	}

	void GameWorld::RenderBoundaries(sf::RenderWindow& window)
	{
		RenderBody(topBorder, window);
		RenderBody(bottomBorder, window);
	}

	void GameWorld::RenderObstacles(sf::RenderWindow& window)
	{
		const auto shift = sf::Vector2f(origin - progress.distance, 0);

		for (auto& o : obstacles) {
			RenderBody(o.topBody, window, shift);
			RenderBody(o.bottomBody, window, shift);
		}
	}

	void GameWorld::RenderPlayer(sf::RenderWindow& window)
	{
		RenderBody(player.body, window, sf::Vector2f(origin - progress.distance, 0));
	}

	void GameWorld::RenderBody(b2Body* body, sf::RenderWindow& window, sf::Vector2f shift)
	{
		auto shape = static_cast<sf::Shape*>(body->GetUserData());
		shape->setPosition(
			Converter::MetersToPixels(body->GetPosition().x) + shift.x,
			Converter::MetersToPixels(body->GetPosition().y) + shift.y
		);
		shape->setRotation(Converter::RadToDeg<double>(body->GetAngle()));
		window.draw(*shape);
	}

	b2Body* GameWorld::createBox(int pos_x, int pos_y, int size_x, int size_y, b2BodyType type)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(
			Converter::PixelsToMeters<double>(pos_x),
			Converter::PixelsToMeters<double>(pos_y)
		);
		bodyDef.type = type;
		b2PolygonShape b2shape;
		b2shape.SetAsBox(
			Converter::PixelsToMeters<double>(size_x / 2.0),
			Converter::PixelsToMeters<double>(size_y / 2.0)
		);
		b2FixtureDef fixtureDef;
		fixtureDef.density = 20;
		fixtureDef.friction = 10;
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