//
// Created by luria on 12/11/2022.
//

#include "Blackboard.h"
Blackboard::Blackboard(Player& player, MapHandler& mapHandler) : player(player), mapHandler(mapHandler)
{
}

void Blackboard::main()
{
  playerPos = player.getSprite()->getPosition();
  if (ghostMode == GhostMode::FLEE)
  {
    std::cout << "true\n";
  }
}
GhostMode Blackboard::getGhostMode() const
{
  return ghostMode;
}
void Blackboard::setGhostMode(GhostMode ghostMode)
{
  Blackboard::ghostMode = ghostMode;
}
const sf::Vector2f& Blackboard::getPlayerPos() const
{
  return playerPos;
}
sf::Vector2i Blackboard::randLocation()
{
  randomInt();
  sf::Vector2i final_loc;
  sf::Vector2i random(2, 2);
  if (mapHandler.tile[1][mapHandler.toIndex(random)] != nullptr && mapHandler.returnCost(mapHandler.toIndex(random) == 0))
  {
    final_loc = sf::Vector2i(mapHandler.toWorld(random));
  }
  else
  {
    randLocation();
  }

  return final_loc;
}
int Blackboard::randomInt()
{
  srand(100);
  return rand()%(30-1 + 1) + 1;
}
