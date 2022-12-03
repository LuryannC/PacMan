//
// Created by luryann on 15/10/2022.
//

#ifndef PACMANSFML_GAMESTATES_H
#define PACMANSFML_GAMESTATES_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Functions.h"
#include <iostream>
#include <memory>
#include "vector"
#include "array"
#include <cmath>

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "MapHandler.h"

class GameStates
{
   public:
    explicit GameStates(sf::RenderWindow& window);
    virtual ~GameStates() = default;
   virtual bool init();
   virtual bool lateInit();
   virtual void update(float dt, sf::Event event, AvailableStates& current_state)              ;
   virtual void render()                      ;
   virtual void mouseClicked(sf::Event event, AvailableStates& current_state) ;
   virtual void keyPressed(sf::Event event, AvailableStates& current_state, float dt)   ;
   virtual void resetState(AvailableStates& current_state);

  protected:
   sf::RenderWindow& window;
   sf::Font font_openSans;
};

#endif // PACMANSFML_GAMESTATES_H
