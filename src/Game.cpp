
#include "Game.h"
#include <cmath>
#include <iostream>

Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
  srand(time(NULL));
  //resources = std::make_unique<ResourceHandler>("Data");
    main_menu = std::make_shared<MainMenu>(window);
    in_game = std::make_shared<InGame>(window);
    game_over = std::make_shared<GameOver>(window);
    leaderboard = std::make_shared<Leaderboard>();


}

bool Game::init()
{

  //
  current_state = AvailableStates::MAIN_MENU;
  state = main_menu;

  // Init GameStates
  //main_menu->init();
  //in_game->init();
  //game_over->init();

  return true;
}

bool Game::lateInit()
{
  if (state != nullptr)
  {
    state->lateInit();
  }
  return true;
}

void Game::update(float dt, sf::Event& event)
{
  switch(current_state)
  {
    case AvailableStates::MAIN_MENU:
      state = main_menu;
      break;
    case AvailableStates::IN_GAME:
      state = in_game;
      break;
    case AvailableStates::LEADERBOARD:
      //state = main_menu;
      break;
    case AvailableStates::GAME_OVER:
      state = game_over;
      break;
  }
  if (!pause)
  {
    state->update(dt, event, current_state);
  }
}

void Game::render()
{
  state->render();
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  state->mouseClicked(event, current_state);
}

void Game::keyPressed(sf::Event event, float dt)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && state == in_game)
  {
    pause = !pause;
  }
  state->keyPressed(event, current_state, dt);
}
