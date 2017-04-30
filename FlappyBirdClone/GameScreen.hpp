#pragma once

#include "Screen.hpp"
#include "MainMenuScreen.hpp"
#include "Player.hpp"
#include "Globals.hpp"

#include <vector>
#include <Box2D.h>
#include <SFML\Graphics.hpp>
#include <SFGUI\Widgets.hpp>

namespace FlappyBirdClone
{
	class GameScreen : Screen
	{
	public:
		virtual void Update(float delta);
		virtual void Render(sf::RenderWindow& window);
		virtual void Initialize(sf::RenderWindow& window);
		virtual void ProcessEvent(sf::Event& event, sf::RenderWindow& window);

		GameScreen();

	private:
		struct State
		{
			virtual void Update(float delta);
			virtual void ProcessEvent(sf::Event& event);
			virtual void OnSet();

		protected:
			State(GameScreen& screen);

			GameScreen& screen;
		};

		static const int scoreLabelId = 0;
		static const int gamePausedLabelId = 1;
		static const int recapWindowId = 2;
		static const int recapScoreLabelId = 3;
		static const int bestScoreLabelId = 4;
		static const int toMainMenuButtonId = 5;

		struct GameWorld
		{
			b2World world;
			b2Body* topBorder;
			b2Body* bottomBorder;
			std::vector<b2Body*> bodies;
			Player player;
			int score;
		} data;

		State* currentState;
		
		void InitializeGui(sf::RenderWindow& window);
		void InitializeWorld(sf::RenderWindow& window);
		void ReturnToMainMenu();
		b2Body* createBox(b2World& world, int pos_x, int pos_y, int size_x, int size_y, b2BodyType type = b2_dynamicBody);

		template <typename StateT>
		void SetState()
		{
			delete currentState;
			currentState = new StateT(*this);
			currentState->OnSet();
		}
	
		struct PlayingState : public State
		{
			PlayingState(GameScreen& screen);
			virtual void Update(float delta);
			virtual void ProcessEvent(sf::Event& event);
			virtual void OnSet();
		};

		struct PausedState : public State
		{
			PausedState(GameScreen& screen);
			virtual void Update(float delta);
			virtual void ProcessEvent(sf::Event& event);
			virtual void OnSet();
		};

		struct JustFailedState : public State
		{
			JustFailedState(GameScreen& screen);
			virtual void Update(float delta);
			virtual void ProcessEvent(sf::Event& event);
			virtual void OnSet();
		};

		struct FailedState : public State
		{
			FailedState(GameScreen& screen);
			virtual void Update(float delta);
			virtual void ProcessEvent(sf::Event& event);
			virtual void OnSet();
		};
	};
}
