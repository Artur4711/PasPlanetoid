#pragma once

#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

class Statek;


class Obiekt : public sf::Sprite {

public:
    Obiekt(const std::string& file,
          std::map <std::string,sf::Image*> Images,
          std::map<std::string,sf::Texture*> Textures,
          std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures);
    void setSpeed(int vel_x,int vel_y, int vel_r);
    virtual void animate(const sf::Time &elapsed,Statek& statek,std::list<Obiekt*>* collisionList=nullptr);
    void setBounds(int left,int right,int top, int bot);
    void calcTrueCP();
    bool isDead() { return this->toKill;}
    bool canCollide();
    void draw(sf::RenderWindow& window);
    bool isCollision(Obiekt* object);
    bool top_left = false;
    bool top_right = false;
    bool bot_left = false;
    bool bot_right = false;
    int boost=1;
    bool toKill=false;
    int hp =60;
protected:
    void bounce();
    void loadCollisionPoints(const std::string& file,
        std::map<std::string,sf::Image*>& images,
        std::map<std::string,sf::Texture*>& txs,
        std::map<std::string,sf::VertexArray>& bcpot);
    float iloczyn_wektorowy(sf::Vector2f& A,sf::Vector2f& B,sf::Vector2f& C);
    sf::VertexArray beginCollisionPoints;
    sf::VertexArray trueCollisionPoints;
    int left;
    int right;
    int top;
    int bot;
    int width;
    int height;
    int vel_x;
    int vel_y;
    int vel_r;
};
