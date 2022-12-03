//
// Created by luria on 03/11/2022.
//

#ifndef PACMANSFML_TILESOBJECT_H
#define PACMANSFML_TILESOBJECT_H

#include <SFML/Graphics.hpp>
#include "../Scripts/Functions.h"
#include <iostream>
#include "../Entities/Entities.h"

class TilesObject : public Entities
{
 public:
  TilesObject(float x, float y, sf::RenderWindow& window, int ID);
  int getId() const;
  int getCost() const;
  void setCost(int cost);
  bool isVisible() const;
  void setVisible(bool visible);
  void setId(int id);
  int tileAsId(sf::Vector2i vector);

 private:
  int id;
  int cost;
  bool visible;


  int CELL_SIZE = 16;
  int MAP_WIDTH = 30;
  int MAP_HEIGHT = 34;
  int HALF_CELL = CELL_SIZE / 2;
};

#endif // PACMANSFML_TILESOBJECT_H
