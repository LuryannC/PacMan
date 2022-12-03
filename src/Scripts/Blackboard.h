//
// Created by luria on 12/11/2022.
//

#ifndef PACMANSFML_BLACKBOARD_H
#define PACMANSFML_BLACKBOARD_H

#include "../Entities/Player.h"
#include "random"
#include "MapHandler.h"

enum class GhostMode
{
  HUNT,
  FLEE
};

class Blackboard
{
 private:
  GhostMode ghostMode;
  MapHandler& mapHandler;
  Player& player;
  sf::Vector2f playerPos;

 public:
  explicit Blackboard(Player& player, MapHandler& mapHandler);
  void main();

  // Ghost related
  GhostMode getGhostMode() const;
  void setGhostMode(GhostMode ghostMode);
  sf::Vector2i randLocation();
  int randomInt();

  // Player related
  const sf::Vector2f& getPlayerPos() const;
};

#endif // PACMANSFML_BLACKBOARD_H
