#include "GameScreen.hpp"

namespace FlappyBirdClone
{
	GameScreen::PlayingState::PlayingState(GameScreen& screen)
		:
		State(screen)
	{}

	void GameScreen::PlayingState::Update(float delta)
	{
		screen.data.world.Step(delta, 10, 10);

		auto dy = screen.data.player.body->GetPosition().y - screen.data.player.prevPos.y;

		if (dy > 0 && screen.data.player.prevPos.y != 0)
			screen.data.player.body->ApplyAngularImpulse(dy * delta * 200, true);

		auto rot = screen.data.player.body->GetAngle();
		rot = rot > 1 ? 1 : rot;
		rot = rot < -1 ? -1 : rot;

		screen.data.player.body->SetTransform(screen.data.player.body->GetWorldCenter(), rot);

		screen.data.player.prevPos = screen.data.player.body->GetPosition();

		auto l = screen.data.player.body->GetContactList();
		if (l != nullptr) {
			std::cout << "game failed!" << std::endl;
			screen.SetState<JustFailedState>();
		}
	}

	void GameScreen::PlayingState::ProcessEvent(sf::Event& event)
	{
		if (event.type == sf::Event::EventType::KeyReleased) {
			if (event.key.code == sf::Keyboard::Space) {
				screen.data.player.body->SetLinearVelocity(b2Vec2(0, 0));
				screen.data.player.body->SetAngularVelocity(0);
				screen.data.player.body->ApplyLinearImpulseToCenter(b2Vec2(0, -160), false);
				screen.data.player.body->ApplyAngularImpulse(-10, true);
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
}