//
// Created by luria on 15/10/2022.
//

#ifndef PACMANSFML_INGAME_H
#define PACMANSFML_INGAME_H
#include "../GameStates.h"
#include "../../Entities/Player.h"
#include "../../GameObjects/TilesObject.h"
#include "../../GameObjects/Coins.h"
#include "../../GameObjects/Cherry.h"
#include "../Pathfinding.h"
#include "../MapHandler.h"
#include "../../Entities/Enemy.h"
#include "../Blackboard.h"
#include "../../GameObjects/PowerPills.h"

class InGame : public GameStates
{
 public:
  InGame(sf::RenderWindow& window);
  ~InGame() override = default;
  bool init() override;
  bool lateInit() override;
  void update(float dt, sf::Event event, AvailableStates& current_state) override;
  void render() override;
  void mouseClicked(sf::Event event, AvailableStates& current_state) override;
  void keyPressed(sf::Event event, AvailableStates& current_state, float dt) override;
  void resetState(AvailableStates& current_state) override;
  void enemyMovement();
  static int randomTile();


  // Blackboard
  std::unique_ptr<Blackboard> blackboard;

  static const int map_tiles = 30*34;
  //std::vector<std::unique_ptr<std::array<std::unique_ptr<sf::Sprite>, map_tiles>>> tiles;
  //std::unique_ptr<std::map<int, sf::Vector2f>()> path_locations;

  std::unique_ptr<MapHandler> mapHandlerM;
  std::unique_ptr<Player> player;
  std::array<std::unique_ptr<Enemy>, 4> enemy;
  //std::array<std::array<std::unique_ptr<TilesObject>, map_tiles>, 3> tile;


 private:


  // Coins, pills and cherry
  std::array<std::unique_ptr<Coins>, map_tiles> coins;
  std::array<std::unique_ptr<PowerPills>, 4> powerPills;

  // Cherry
  std::unique_ptr<Cherry> cherry;
  sf::Clock cherry_clock;

  // HUD
  sf::Font font_openSans;

  sf::Text hud_score;
  sf::Text lives;
  unsigned int score = 0;
  int coins_collected;
  std::vector<int> available_coins;

  // Enemy AI
  float time_to_chase = 10.f;
  float flee_duration = 4.5f;
  float chase_player_duration = 5.f;
  sf::Clock reset_state;
  std::array<sf::Clock, 2> chase_player;
  bool chasing_player;
  std::array<sf::Clock, 4> change_path;
  std::array<float, 4> change_frequency = { 5.0f, 5.8f, 5.6f, 3.8f };
  sf::Clock release_time;
  bool returning_to_spawn = false;

  // Teleport points
  sf::RectangleShape teleport_points[2];

  /// Audio
  sf::Music main_music;
  bool start_music = true;

  // View
//  bool set_view = false;
//  sf::View camera;
//  float tiles_x = 30*16;
//  float tiles_y = 34*16;

};

#endif // PACMANSFML_INGAME_H
