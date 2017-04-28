#include "GameScreen.hpp"

#include "Box2dConverter.hpp"

#include <Box2D.h>

namespace FlappyBirdClone
{
	GameScreen::GameScreen()
		:
		world(b2Vec2(0, 9.8f)),
		prevPos(b2Vec2_zero)
	{
	}

	void GameScreen::Update(float delta)
	{
		world.Step(delta, 10, 10);

		auto dy = player.body->GetPosition().y - prevPos.y;

		if (dy > 0 && prevPos.y != 0)
		player.body->ApplyAngularImpulse(dy * delta * 200, true);

		auto rot = player.body->GetAngle();
		rot = rot > 1 ? 1 : rot;
		rot = rot < -1 ? -1 : rot;

		player.body->SetTransform(player.body->GetWorldCenter(), rot);
		
		prevPos = player.body->GetPosition();

		auto l = player.body->GetContactList();
		if (l != nullptr) {
			auto b = l->contact->GetFixtureA()->GetBody();
			if (b == player.body) {
				b = l->contact->GetFixtureB()->GetBody();
			}

			if (b == bodies.front()) {
				std::cout << "game failed!" << std::endl;
			}
		}
	}

	void GameScreen::Render(sf::RenderWindow& window)
	{
		Screen::Render(window);

		for (b2Body* body = world.GetBodyList(); body != nullptr; body = body->GetNext()) {
			sf::Shape* shape = static_cast<sf::Shape*>(body->GetUserData());
			shape->setPosition(Converter::MetersToPixels(body->GetPosition().x), Converter::MetersToPixels(body->GetPosition().y));
			shape->setRotation(Converter::RadToDeg<double>(body->GetAngle()));
			window.draw(*shape);
		}
	}

	void GameScreen::Initialize(sf::RenderWindow& window)
	{
		Screen::Initialize(window);

		bodies.push_back(createBox(
			world,
			window.getSize().x / 2,
			window.getSize().y,
			8000,
			40,
			b2BodyType::b2_staticBody
		));

		player.body = createBox(world,
			window.getSize().x / 2,
			window.getSize().y / 2,
			60,
			40,
			b2BodyType::b2_dynamicBody);

		bodies.push_back(player.body);
	}

	void GameScreen::ProcessEvent(sf::Event& event, sf::RenderWindow& window)
	{
		if (event.type == sf::Event::EventType::KeyReleased) {
			if (event.key.code == sf::Keyboard::Space) {
				player.body->SetLinearVelocity(b2Vec2(0, 0));
				player.body->SetAngularVelocity(0);
				player.body->ApplyLinearImpulseToCenter(b2Vec2(0, -160), false);
				player.body->ApplyAngularImpulse(-10, true);
			}
		}
	}

	b2Body* GameScreen::createBox(b2World& world, int pos_x, int pos_y, int size_x, int
		size_y, b2BodyType type)
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