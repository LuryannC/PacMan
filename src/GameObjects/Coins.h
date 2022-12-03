//
// Created by luria on 06/11/2022.
//

#ifndef PACMANSFML_COINS_H
#define PACMANSFML_COINS_H
#include "../Entities/Entities.h"

class Coins : public Entities
{
 public:
  Coins(float x, float y, sf::RenderWindow& window, int ID);
  bool isVisible() const;
  void setVisible(bool visible);
  int getId() const;

 private:
  bool visible = true;
  int id;
};

#endif // PACMANSFML_COINS_H
