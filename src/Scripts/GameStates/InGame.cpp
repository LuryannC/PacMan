//
// Created by luria on 15/10/2022.
//

#include "InGame.h"
#include <fstream>

InGame::InGame(sf::RenderWindow& window) : GameStates(window)
{

  mapHandlerM = std::make_unique<MapHandler>(window);
  player = std::make_unique<Player>(528, 379,window, mapHandlerM->tile);
  blackboard = std::make_unique<Blackboard>(*player, *mapHandlerM);
  init();
}

bool InGame::init()
{
  /// Camera
  //camera = window.getDefaultView();


  /// Set camera center
//  std::pair<float, float> map_center_px;
//  map_center_px.first = tiles_x * 0.5f + 16 * 0.5f;
//  map_center_px.second = tiles_y * 0.5f + 16 * 0.5f;

//  camera.setCenter(map_center_px.first, map_center_px.second);
  //camera.zoom(0.8f);

  // Music
  main_music.openFromFile("Data/Audio/gameMusic.ogg");
  main_music.setVolume(10);
  //main_music.play();

  mapHandlerM->init();
  player->init();

  /// Restart clocks
  for (auto clock : chase_player)
  {
    clock.restart();
  }
  for (auto clock : change_path)
  {
    clock.restart();
  }

  /// Initialise enemies
  enemy[0] = std::make_unique<Enemy>(mapHandlerM->tile[1][462]->getSprite()->getPosition().x, mapHandlerM->tile[1][462]->getSprite()->getPosition().y, window, 16);
  enemy[1] = std::make_unique<Enemy>(mapHandlerM->tile[1][463]->getSprite()->getPosition().x, mapHandlerM->tile[1][462]->getSprite()->getPosition().y, window, 32);
  enemy[2] = std::make_unique<Enemy>(mapHandlerM->tile[1][464]->getSprite()->getPosition().x, mapHandlerM->tile[1][462]->getSprite()->getPosition().y, window, 48);
  enemy[3] = std::make_unique<Enemy>(mapHandlerM->tile[1][465]->getSprite()->getPosition().x, mapHandlerM->tile[1][462]->getSprite()->getPosition().y, window, 64);

  for (auto & enemies : enemy)
  {
    enemies->init();
  }

  ///Make Cherry
  cherry = std::make_unique<Cherry>(mapHandlerM->tile[1][555]->getSprite()->getPosition().x, mapHandlerM->tile[1][555]->getSprite()->getPosition().y, window);
  cherry_clock.restart();

  /// Make Power Pills
  powerPills[0] = std::make_unique<PowerPills>(mapHandlerM->tile[1][31]->getSprite()->getPosition().x, mapHandlerM->tile[1][31]->getSprite()->getPosition().y, window, 31);
  powerPills[1] = std::make_unique<PowerPills>(mapHandlerM->tile[1][58]->getSprite()->getPosition().x, mapHandlerM->tile[1][58]->getSprite()->getPosition().y, window, 58);
  powerPills[2] = std::make_unique<PowerPills>(mapHandlerM->tile[1][961]->getSprite()->getPosition().x, mapHandlerM->tile[1][961]->getSprite()->getPosition().y, window, 961);
  powerPills[3] = std::make_unique<PowerPills>(mapHandlerM->tile[1][988]->getSprite()->getPosition().x, mapHandlerM->tile[1][988]->getSprite()->getPosition().y, window, 988);

  /// Make Coins
  unsigned int coin_index = 0;
  for (const auto& coin_location : mapHandlerM->tile[2])
  {
    if (coin_location != nullptr)
    {
      float pos_x = coin_location->getSprite()->getPosition().x;
      float pos_y = coin_location->getSprite()->getPosition().y;
      int id = coin_location->getId();
      coins.at(coin_index) = std::make_unique<Coins>(pos_x, pos_y, window, id);
      available_coins.push_back(coin_index);
    }
    coin_index++;
  }

  ///in game HUD
  font_openSans.loadFromFile("Data/Fonts/OpenSans-Bold.ttf");

  Functions::generate(hud_score,
                      std::to_string(score),
                      font_openSans,
                      sf::Color::Yellow,
                      window.getSize().x - 150,
                      100,
                      25);

  Functions::generate(lives,
                      "Lives: " + std::to_string(player->getLives()),
                      font_openSans,
                      sf::Color::Yellow,
                      window.getSize().x - 150,
                      50,
                      25);


/// Teleport points
  for (auto & teleport_point : teleport_points)
  {
    teleport_point.setSize(sf::Vector2f(16,28));
    teleport_point.setFillColor(sf::Color::Black);
  }

  teleport_points[0].setPosition(mapHandlerM->tile[1][479]->getSprite()->getPosition().x, mapHandlerM->tile[1][479]->getSprite()->getPosition().y - 4);
  teleport_points[1].setPosition(mapHandlerM->tile[1][450]->getSprite()->getPosition().x, mapHandlerM->tile[1][450]->getSprite()->getPosition().y - 4);


  return GameStates::init();
}
bool InGame::lateInit()
{
  return GameStates::lateInit();
}
void InGame::update(float dt, sf::Event event, AvailableStates& current_state)
{
//  if (!set_view)
//  {
//    window.setView(camera);
//    set_view = true;
//  }

  if (start_music)
  {
    main_music.play();

    /// Reset some clocks
    cherry_clock.restart();
    release_time.restart();

    // Turn off access
    start_music = false;
  }
  player->update(dt);
  //blackboard->main();


  /// Check collision with the player to remove life.
  for (auto & enemies : enemy)
  {
    enemies->update(dt);
    if (enemies->checkCollision(*player->getSprite()) &&
      static_cast<AnimationState>(enemies->getState()) == AnimationState::HUNT)
    {

      player->setLives(player->getLives() - 1);
      player->getSprite()->setPosition(mapHandlerM->tile[1][555]->getSprite()->getPosition());
      player->setMovement({0,0});
      player->setDesiredVector({0,0});
      lives.setString("Lives: " + std::to_string(player->getLives()));
      cherry->reset();
      cherry_clock.restart();
      release_time.restart();
      for (auto & i : enemy)
      {
        i->reset();
      }
    }
    else if (enemies->checkCollision(*player->getSprite()) &&
             static_cast<AnimationState>(enemies->getState()) == AnimationState::FLEE)
    {
      score += 200;
      static sf::Vector2i desired_pos(mapHandlerM->tile[1][464]->getSprite()->getPosition().x + 8, mapHandlerM->tile[1][464]->getSprite()->getPosition().y + 8);
      enemies->setDestination(Pathfinder(*mapHandlerM, desired_pos, *enemies->getSprite()));
      enemies->setSpeed(320);
      returning_to_spawn = true;
    }
    if (player->getLives() == 0)
    {
      resetState(current_state);
      current_state = AvailableStates::GAME_OVER;
      main_music.stop();
    }


    /// Make ghosts steal the coins
//    if (coins[mapHandlerM->toIndex(sf::Vector2i(enemies->getSprite()->getPosition()))] != nullptr)
//    {
//      coins[mapHandlerM->toIndex(sf::Vector2i(enemies->getSprite()->getPosition()))] = nullptr;
//      score += 50;
//      coins_collected++;
//      hud_score.setString(std::to_string(score));
//    }
  }

  /// Collect pills
  for (auto & powerPill : powerPills)
  {
    if (powerPill != nullptr && player->playerPosAsID() == powerPill->getId() && powerPill->isVisible())
    {
      for (const auto& enem : enemy)
      {
       enem->setState(static_cast<int>(AnimationState::FLEE));
       reset_state.restart();
      }
      powerPill->setVisible(false);
    }
  }

  /// Cherry logic
  if (cherry_clock.getElapsedTime().asSeconds() > 10.f && !cherry->isVisible())
  {
    cherry->setVisible(true);
  }

  if (player->playerPosAsID() == 555 && cherry->isVisible())
  {
    score += 500;
    hud_score.setString(std::to_string(score));
    cherry->setVisible(false);
    cherry_clock.restart();
  }


  /// Reset enemy to hunt the player
  if (static_cast<AnimationState>(enemy[0]->getState()) == AnimationState::FLEE && reset_state.getElapsedTime().asSeconds() > flee_duration)
  {
    for (const auto& enem : enemy)
    {
      enem->setState(static_cast<int>(AnimationState::HUNT));
    }
  }

  /// check coins collected
  if (coins[player->playerPosAsID()] != nullptr && coins[player->playerPosAsID()]->isVisible())
  {
    //coins[player->playerPosAsID()] = nullptr;
    coins[player->playerPosAsID()]->setVisible(false);
    score += 50;
    coins_collected += 1;
    hud_score.setString(std::to_string(score));
  }

  /// Enemy movement
  enemyMovement();

  /// Win condition
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
  {
    coins_collected = available_coins.size();
  }

  if (coins_collected == available_coins.size())
  {
    resetState(current_state);
    current_state = AvailableStates::GAME_OVER;
    main_music.stop();
  }
  GameStates::update(dt, event, current_state);
}
void InGame::render()
{
  /// Render tiles
  for (int j = 0; j < mapHandlerM->map.getLayers().size(); j++)
  {
    for (int i = 0; i < 30 * 34; i++)
    {
      if (mapHandlerM->tile[j][i] != nullptr)
      {
        window.draw(*mapHandlerM->tile[j][i]->getSprite());
      }
    }
  }

  /// Render coins
  for (const auto& coin : coins)
  {
    if (coin != nullptr && coin->isVisible())
    {
      window.draw(*coin->getSprite());
    }
  }
  /// Render Enemies
  for(auto & enemies : enemy)
  {
    window.draw(*enemies->getSprite());
  }

  /// Render HUD
  window.draw(hud_score);
  window.draw(lives);

  /// Render Power Pills
  for (auto & power_pill : powerPills)
  {
    if (power_pill->isVisible())
    {
      window.draw(*power_pill->getSprite());
    }
  }

  if (cherry->isVisible())
  {
    window.draw(*cherry->getSprite());
  }

  player->render();

  window.draw(teleport_points[0]);
  window.draw(teleport_points[1]);

  GameStates::render();
}
void InGame::mouseClicked(sf::Event event, AvailableStates& current_state)
{
  GameStates::mouseClicked(event, current_state);
}
void InGame::keyPressed(sf::Event event, AvailableStates& current_state, float dt)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
  {
    std::cout << player->playerPosAsID() << std::endl;
    std::cout << player->getSprite()->getPosition().x << std::endl;
  }
  player->keyPressed(event, dt);
  GameStates::keyPressed(event, current_state, dt);
}
void InGame::resetState(AvailableStates& current_state)
{
  cherry_clock.restart();
  cherry->reset();
  start_music = true;
  player->reset();
  for (auto & ghost : enemy)
  {
    ghost->reset();
  }
  score = 0;
  hud_score.setString(std::to_string(score));
  for (auto & coin : coins)
  {
    if (coin != nullptr && !coin->isVisible())
    {
        coin->setVisible(true);
    }
  }
  for (auto & power_pill : powerPills)
  {
    if (!power_pill->isVisible())
    {
      power_pill->reset();
    }
  }
  coins_collected = 0;
  GameStates::resetState(current_state);
}
void InGame::enemyMovement()
{
  for (auto & current_enemy : enemy)
  {
    if (returning_to_spawn && current_enemy->getDestination().empty())
    {
      returning_to_spawn = false;
    }
  }
  if (static_cast<AnimationState>(enemy[0]->getState()) == AnimationState::HUNT && !returning_to_spawn)
  {
    /// Reset enemies speed
    for (auto & current_enemy : enemy)
    {
      current_enemy->setSpeed(45);
    }
    if (chase_player[0].getElapsedTime().asSeconds() > time_to_chase)
    {
      chasing_player = true;
      chase_player[0].restart();
      chase_player[1].restart();
    }
    for (int i = 0; i < enemy.size(); ++i)
    {
      int tile = randomTile();
      if(mapHandlerM->tile[1][tile] != nullptr && (change_path[i].getElapsedTime().asSeconds() > change_frequency[i] || enemy[i]->getDestination().empty()) && chase_player[1].getElapsedTime().asSeconds() > chase_player_duration)
      {
        sf::Vector2i desired_pos(mapHandlerM->tile[1][tile]->getSprite()->getPosition().x + 8, mapHandlerM->tile[1][tile]->getSprite()->getPosition().y + 8);
        enemy[i]->setDestination(Pathfinder(*mapHandlerM, desired_pos, *enemy[i]->getSprite()));
        change_path[i].restart();
        chasing_player = false;
      }
      else if (chasing_player)
      {
        sf::Vector2i desired_pos(
          player->getSprite()->getPosition().x + 8,
          player->getSprite()->getPosition().y + 8);
        enemy[i]->setDestination(
          Pathfinder(*mapHandlerM, desired_pos, *enemy[i]->getSprite()));
      }
    }
  }
  else
  {
    for (int i = 0; i < enemy.size(); ++i)
    {
      int tile = randomTile();
      if(mapHandlerM->tile[1][tile] != nullptr && change_path[i].getElapsedTime().asSeconds() > change_frequency[i])
      {
        enemy[i]->setSpeed(25);
        sf::Vector2i desired_pos(mapHandlerM->tile[1][tile]->getSprite()->getPosition().x + 8, mapHandlerM->tile[1][tile]->getSprite()->getPosition().y + 8);
        enemy[i]->setDestination(Pathfinder(*mapHandlerM, desired_pos, *enemy[i]->getSprite()));
        change_path[i].restart();
      }
    }
  }
}
int InGame::randomTile()
{
  return rand()%(1020 + 1);
}

