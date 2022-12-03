//
// Created by luria on 28/11/2022.
//

#ifndef PACMANSFML_CHERRY_H
#define PACMANSFML_CHERRY_H
#include "../Entities/Entities.h"

class Cherry : public Entities
{
 public:
  Cherry(float x, float y, sf::RenderWindow& window);
  bool isVisible() const;
  void setVisible(bool visible);
  void reset() override;


 private:
  bool visible = false;
};

#endif // PACMANSFML_CHERRY_H
