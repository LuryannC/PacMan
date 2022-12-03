//
// Created by luria on 10/11/2022.
//

#ifndef PACMANSFML_ENEMY_H
#define PACMANSFML_ENEMY_H
#include "Entities.h"

class Enemy : public Entities
{
 public:
  Enemy(float x, float y, sf::RenderWindow& window, int start_rect);
  bool init();
  void update(float dt) override;
  bool checkCollision(sf::Sprite entity);
  void reset() override;
  void AnimationHandler();

  // State
  int getState() const;
  void setState(int state);

 private:
  int rect_pos;
  sf::IntRect frame;
  int state;
  sf::Clock animation_clock;
  float update_rate = 0.1f;
};

#endif // PACMANSFML_ENEMY_H
