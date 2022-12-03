
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include "./Scripts/GameStates/MainMenu.h"
#include "./Scripts/GameStates/InGame.h"
#include "./Scripts/GameStates/GameOver.h"
#include "ResourceHandler.h"
#include <SFML/Graphics.hpp>
#include "./Scripts/MapHandler.h"
#include <memory>
#include "vector"
#include "array"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "./Scripts/MapHandler.h"
#include "./Scripts/Leaderboard.h"
#include "./Scripts/BehaviourTree.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game() = default;
  bool init();
  bool lateInit();
  void update(float dt, sf::Event& event);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event, float dt);


  sf::Text game_title;
  sf::Font font_openSans;


 private:
  sf::RenderWindow& window;
  //std::unique_ptr<ResourceHandler> resources;

  // Game State
  std::shared_ptr<GameStates> state;

  AvailableStates current_state;

  // Game State Classes
  std::shared_ptr<MainMenu> main_menu;
  std::shared_ptr<InGame> in_game;
  std::shared_ptr<GameOver> game_over;
  std::shared_ptr<Leaderboard> leaderboard;
  std::unique_ptr<BehaviourTree> behaviourTree;

  bool pause = false;
  bool init_class[4] = {false, false, false, false};

};

#endif // PLATFORMER_GAME_H
