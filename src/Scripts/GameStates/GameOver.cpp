//
// Created by luria on 15/10/2022.
//

#include "GameOver.h"
GameOver::GameOver(sf::RenderWindow& window) : GameStates(window)
{
  init();
}
bool GameOver::init()
{
  // Generate Game Title
  Functions::generate(game_title,
                      "PAC-MAN",
                      font_openSans,
                      sf::Color::White,
                      0,
                      0,
                      140);

  // Generate Play Button
  Functions::generate(play_button,
                      "Play Again",
                      font_openSans,
                      sf::Color::White,
                      0,
                      0,
                      40);

  // Generate Exit Button
  Functions::generate(exit_button,
                      "Exit",
                      font_openSans,
                      sf::Color::White,
                      0,
                      0,
                      40);

  // Title
  game_title.setStyle(sf::Text::Bold);
  game_title.setPosition((float )Functions::centerTextX(game_title, half_window * 0.4f), 20);

  return GameStates::init();
}
void GameOver::update(float dt, sf::Event event, AvailableStates& current_state)
{
  // Buttons
  inside_play = buttonFunction(play_button, event, 320, 305);
  inside_exit = buttonFunction(exit_button, event, 410, 395);
  GameStates::update(dt, event, current_state);
}
void GameOver::render()
{
  window.draw(game_title);
  window.draw(play_button);
  window.draw(exit_button);
  GameStates::render();
}
void GameOver::mouseClicked(sf::Event event, AvailableStates& current_state)
{
  if (inside_play)
  {
    current_state = AvailableStates::MAIN_MENU;
  }
  else if (inside_exit)
  {
    window.close();
  }
  GameStates::mouseClicked(event, current_state);
}
void GameOver::keyPressed(sf::Event event, AvailableStates& current_state, float dt)
{
  GameStates::keyPressed(event, current_state, dt);
}
void GameOver::resetState(AvailableStates& current_state)
{
  GameStates::resetState(current_state);
}
bool GameOver::buttonFunction(sf::Text& text, sf::Event event,float previous_y, float next_y)
{
  if (Functions::insideText(event, text))
  {
    text.setCharacterSize(60);
    text.setPosition((float )Functions::centerTextX(text, half_window), next_y);
    text.setFillColor(sf::Color(255, 255, 0, 255));
    return true;
  }
  else
  {
    text.setCharacterSize(40);
    text.setPosition((float )Functions::centerTextX(text, half_window), previous_y);
    text.setFillColor(sf::Color::White);
    return false;
  }
}
