//
// Created by luria on 15/10/2022.
//

#ifndef PACMANSFML_GAMEOVER_H
#define PACMANSFML_GAMEOVER_H
#include "../GameStates.h"

class GameOver : public GameStates
{
 public:
  GameOver(sf::RenderWindow& window);
  ~GameOver() override = default;
  bool init() override;
  void update(float dt, sf::Event event, AvailableStates& current_state) override;
  void render() override;
  void mouseClicked(sf::Event event, AvailableStates& current_state) override;
  void keyPressed(sf::Event event, AvailableStates& current_state, float dt) override;
  void resetState(AvailableStates& current_state) override;
  bool buttonFunction(sf::Text& text, sf::Event event, float previous_y, float next_y);


 private:
  int half_window = 540;

  sf::Text game_title;
  sf::Text play_button;
  sf::Text exit_button;

  // Button bool
  bool inside_play;
  bool inside_exit;


};

#endif // PACMANSFML_GAMEOVER_H
