//
// Created by luria on 15/10/2022.
//

#include "MainMenu.h"
MainMenu::MainMenu(sf::RenderWindow& window) : GameStates(window)
{
  init();
}
bool MainMenu::init()
{
  background_texture.loadFromFile("Data/Images/Pac-ManBG.png");
  background.setTexture(background_texture);

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
                      "Play",
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

  std::cout << "Main Menu init" << std::endl;
  /// Audio
  if (!start_buffer.loadFromFile("Data/Audio/StartGame.ogg"))
  {
    std::cout << "hit_buffer did not load" << std::endl;
  }

  start_audio.setBuffer(start_buffer);
  start_audio.setVolume(100);



  return GameStates::init();
}

bool MainMenu::lateInit()
{
  // Title
  game_title.setStyle(sf::Text::Bold);
  game_title.setPosition((float )Functions::centerTextX(game_title, half_window), 20);

  // Play button
  play_button.setPosition((float )Functions::centerTextX(play_button, half_window), 320);

  // Exit button
  exit_button.setPosition((float)Functions::centerTextX(exit_button, half_window), 480);

  return GameStates::lateInit();
}

void MainMenu::update(float dt, sf::Event event, AvailableStates& current_state)
{
  // Buttons
  inside_play = buttonFunction(play_button, event, 320, 305);
  inside_exit = buttonFunction(exit_button, event, 410, 395);

  if (started && start_delay.getElapsedTime().asSeconds() > 2.f)
  {
    current_state = AvailableStates::IN_GAME;
    started = false;
  }

  GameStates::update(dt, event, current_state);
}
void MainMenu::render()
{
  window.draw(background);
  window.draw(game_title);
  window.draw(play_button);
  window.draw(exit_button);
  GameStates::render();
}
void MainMenu::mouseClicked(sf::Event event, AvailableStates& current_state)
{
  if (inside_play && !started)
  {
    //start_audio.play();
    //start_delay.restart();

    //main_music.play();
    started = true;
  }
  else if (inside_exit)
  {
    window.close();
  }
  GameStates::mouseClicked(event, current_state);
}
void MainMenu::keyPressed(sf::Event event, AvailableStates& current_state, float dt)
{
  GameStates::keyPressed(event, current_state, dt);
}

void MainMenu::resetState(AvailableStates& current_state)
{
  GameStates::resetState(current_state);
}

bool MainMenu::buttonFunction(sf::Text& text, sf::Event event,float previous_y, float next_y)
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
