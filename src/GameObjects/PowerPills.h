//
// Created by luria on 21/11/2022.
//

#ifndef PACMANSFML_POWERPILLS_H
#define PACMANSFML_POWERPILLS_H

#include "../Entities/Entities.h"

class PowerPills : public Entities
{
 public:
  PowerPills(float x, float y, sf::RenderWindow& window, int ID);
  bool checkCollision(sf::Sprite entity);
  bool isVisible() const;
  void setVisible(bool visible);
  int getId() const;
  void reset() override;

 private:
  bool visible = true;
  int id;

};

#endif // PACMANSFML_POWERPILLS_H
