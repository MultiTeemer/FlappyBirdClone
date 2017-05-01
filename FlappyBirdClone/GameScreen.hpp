#pragma once

#include "Screen.hpp"
#include "MainMenuScreen.hpp"
#include "GameWorld.h"
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
		static const float playerSpeed;

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

		GameWorld gameWorld;

		State* currentState;
		
		void InitializeGui(sf::RenderWindow& window);
		void ReturnToMainMenu();

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
		
		private:
			void AdvanceProgress(float delta, float speed);
			void CheckFail();
			void CheckObstaclesPassing();
			void UpdateWorld(float delta);
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
