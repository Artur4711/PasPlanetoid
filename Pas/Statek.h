#pragma once

#include <SFML/Graphics.hpp>
#include <Obiekty.h>

class Statek : public Obiekty
{
public:
    Statek(sf::Vector2f size,sf::Vector2f position);
    void animate(const sf::Time &elapse);
//    void kolizja(std::string where);
    bool top_left = false;
    bool top_right = false;
    bool bot_left = false;
    bool bot_right = false;
private:

};
