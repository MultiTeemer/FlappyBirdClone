#include "GameScreen.hpp"

#include "Box2dConverter.hpp"

namespace FlappyBirdClone
{
	GameScreen::PlayingState::PlayingState(GameScreen& screen)
		:
		State(screen)
	{}

	void GameScreen::PlayingState::Update(float delta)
	{
		AdvanceProgress(delta, GameWorld::PlayerSpeed);
		UpdateWorld(delta);
		CheckObstaclesPassing();
		CheckFail();
	}

	void GameScreen::PlayingState::ProcessEvent(sf::Event& event)
	{
		if (event.type == sf::Event::EventType::KeyReleased || event.type == sf::Event::EventType::MouseButtonReleased) {
			if (event.key.code == sf::Keyboard::Space || event.mouseButton.button == sf::Mouse::Left) {
				screen.gameWorld.player.body->SetLinearVelocity(b2Vec2(0, 0));
				screen.gameWorld.player.body->SetAngularVelocity(0);
				screen.gameWorld.player.body->ApplyLinearImpulseToCenter(b2Vec2(0, -160), false);
				screen.gameWorld.player.body->ApplyAngularImpulse(-10, true);
			}

			if (event.key.code == sf::Keyboard::Escape) {
				screen.SetState<PausedState>();
			}
		}
	}

	void GameScreen::PlayingState::OnSet()
	{
		screen.Ui.Get<sfg::Label>(GameScreen::scoreLabelId)->Show(true);

		screen.Ui.Get<sfg::Label>(GameScreen::gamePausedLabelId)->Show(false);
		screen.Ui.Get<sfg::Window>(GameScreen::recapWindowId)->Show(false);
	}

	void GameScreen::PlayingState::AdvanceProgress(float delta, float speed)
	{
		screen.gameWorld.progress.distance += delta * speed;

		const auto pos = screen.gameWorld.player.body->GetPosition();
		screen.gameWorld.player.body->SetTransform(
			b2Vec2(pos.x + Converter::PixelsToMeters(delta * speed), pos.y),
			screen.gameWorld.player.body->GetAngle()
		);

		screen.gameWorld.obstaclesManager.Update();
	}

	void GameScreen::PlayingState::CheckObstaclesPassing()
	{
		const auto firstNotPassedObstacle = std::find_if(
			screen.gameWorld.obstacles.begin(),
			screen.gameWorld.obstacles.end(),
			[](const Obstacle& o) -> bool {
				return !o.passed;
			}
		);

		if (firstNotPassedObstacle != screen.gameWorld.obstacles.end()) {
			if (screen.gameWorld.progress.distance >= firstNotPassedObstacle->position) {
				++screen.gameWorld.progress.score;
				firstNotPassedObstacle->passed = true;

				screen.Ui.Get<sfg::Label>(GameScreen::scoreLabelId)->SetText(std::to_string(screen.gameWorld.progress.score));
			}
		}
	}

	void GameScreen::PlayingState::CheckFail()
	{
		auto l = screen.gameWorld.player.body->GetContactList();
		if (l != nullptr) {
			screen.SetState<JustFailedState>();
		}
	}

	void GameScreen::PlayingState::UpdateWorld(float delta)
	{
		screen.gameWorld.world.Step(delta, 10, 10);

		auto dy = screen.gameWorld.player.body->GetPosition().y - screen.gameWorld.player.prevPos.y;

		if (dy > 0 && screen.gameWorld.player.prevPos.y != 0)
			screen.gameWorld.player.body->ApplyAngularImpulse(dy * delta * 200, true);

		auto rot = screen.gameWorld.player.body->GetAngle();
		rot = rot > 1 ? 1 : rot;
		rot = rot < -1 ? -1 : rot;

		screen.gameWorld.player.body->SetTransform(screen.gameWorld.player.body->GetWorldCenter(), rot);

		screen.gameWorld.player.prevPos = screen.gameWorld.player.body->GetPosition();
	}
}