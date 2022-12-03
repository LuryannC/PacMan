//
// Created by luria on 15/10/2022.
//

#ifndef PACMANSFML_MAINMENU_H
#define PACMANSFML_MAINMENU_H
#include "../GameStates.h"

class MainMenu : public GameStates
{
 public:
  MainMenu(sf::RenderWindow& window);
  ~MainMenu() override = default;
  bool init() override;
  bool lateInit() override;
  void update(float dt, sf::Event event, AvailableStates& current_state) override;
  void render() override;
  void mouseClicked(sf::Event event, AvailableStates& current_state) override;
  void keyPressed(sf::Event event, AvailableStates& current_state, float dt) override;
  void resetState(AvailableStates& current_state) override;

  bool buttonFunction(sf::Text& text, sf::Event event, float previous_y, float next_y);

 private:


  // Background
  sf::Sprite background;
  sf::Texture background_texture;

  // Useful
  int half_window = 540;

  bool initialized = false;
  // Text
  sf::Text game_title;
  sf::Text play_button;
  sf::Text exit_button;

  // Button bool
  bool inside_play;
  bool inside_exit;

  // Audio
  sf::Sound start_audio;
  sf::SoundBuffer start_buffer;

  // Start delay
  sf::Clock start_delay;
  bool started;


};

#endif // PACMANSFML_MAINMENU_H
