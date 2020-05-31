#pragma once

#include <SFML/Graphics.hpp>
#include <Obiekty.h>

class Statek : public Obiekty
{
public:
    Statek(sf::Vector2f size,sf::Vector2f position);
    void animate(const sf::Time &elapse);
    void setBounds(int left,int right,int top, int bot); //nadpisana identyczna metoda żeby działało
    void kolizja(std::string where);
private:
    void bounce();
    int vel_x_=0;
    int vel_y_=0;
    int vel_r_=0;
    int left=0;
    int right=0;
    int top=0;
    int bot=0;
    bool top_left = false;
    bool top_right = false;
    bool bot_left = false;
    bool bot_right = false;

};
