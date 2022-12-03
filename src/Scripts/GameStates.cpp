//
// Created by luryann on 15/10/2022.
//

#include "GameStates.h"
GameStates::GameStates(sf::RenderWindow& window) :  window(window)
{}
bool GameStates::init()
{
  font_openSans.loadFromFile("Data/Fonts/OpenSans-Bold.ttf");
  return false;
}
bool GameStates::lateInit()
{
  return false;
}
void GameStates::update(float dt, sf::Event event, AvailableStates& current_state) {}
void GameStates::render() {}
void GameStates::mouseClicked(sf::Event event, AvailableStates& current_state) {}
void GameStates::keyPressed(sf::Event event, AvailableStates& current_state, float dt) {}
void GameStates::resetState(AvailableStates& current_state) {}
