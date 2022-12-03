#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
  std::cout << "You should see a window that opens as well as this writing to console..."
            << std::endl;

  // create window and set up
  sf::RenderWindow window(sf::VideoMode(1080, 720), "Pacman game", sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);
//  sf::View view(sf::FloatRect(0.f, 0.f, 1080.f, 720.f));
//  view.zoom(0.9);
//  window.setView(view);


  //initialise an instance of the game class
  Game game(window);

  //run the init function of the game class and check it all initialises ok
  if (!game.init())
  {
    return 0;
  }
  if (!game.lateInit())
  {
    return 0;
  }

  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;

    //calculate delta time
    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    //'process inputs' element of the game loop
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed)
        game.keyPressed(event, dt);

      if (event.type == sf::Event::MouseButtonPressed)
      {
        game.mouseClicked(event);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        window.close();
    }


    //'update' element of the game loop
    game.update(dt, event);

    window.clear(sf::Color::Black);

    //'render' element of the game loop
    game.render();
    window.display();
  }

  return 0;
}
