#include <Statek.h>
#include <iostream>

Statek::Statek(const std::string& file,
       std::map <std::string,sf::Image*>Images,
       std::map<std::string,sf::Texture*> Textures,
       std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures) : Obiekty(file,Images,Textures,beginCollisionPointsOfTextures) {
}

void Statek::draw(sf::RenderWindow& window) {
    window.draw(*this);
    //window.draw(trueCollisionPoints);
    //tu ewentualne animacje
}

void Statek::animate(sf::Time elapsed,std::map<int,bool>& status,std::list <Obiekty*> &Asteroidy) {
    sf::FloatRect statek = getGlobalBounds();
    if(status[sf::Keyboard::D]&&this->right>=statek.left+statek.width) {
        move(100*elapsed.asSeconds()+2,0);
    }
    if(status[sf::Keyboard::A]&&this->left<=statek.left) {
        move(-100*elapsed.asSeconds()-2,0);
    }
    if(status[sf::Keyboard::W]&&this->top<=statek.top) {
        move(0,-100*elapsed.asSeconds()-2);
    }
    if(status[sf::Keyboard::S]&&this->bot>=statek.top+statek.height) {
        move(0,100*elapsed.asSeconds()+2);
    }
    calcTrueCP();

    for (auto as : Asteroidy) {
        if (isCollision(as)) {
            if(top_right&&bot_right){
                move(-2000*elapsed.asSeconds(),0);
                as->move(2000*elapsed.asSeconds(),0);
                top_right=false;
                bot_right=false;
            }
            if(top_left&&top_right){
                move(0,2000*elapsed.asSeconds());
                as->move(0,-2000*elapsed.asSeconds());
                top_left=false;
                top_right=false;
            }
            if(top_left&&bot_left){
                move(2000*elapsed.asSeconds(),0);
                as->move(-2000*elapsed.asSeconds(),0);
                top_left=false;
                bot_left=false;
            }
            if(top_left){
                move(2000*elapsed.asSeconds(),2000*elapsed.asSeconds());
                as->move(-2000*elapsed.asSeconds(),-2000*elapsed.asSeconds());
                top_left=false;
            }
            if(top_right){
                move(-2000*elapsed.asSeconds(),2000*elapsed.asSeconds());
                as->move(2000*elapsed.asSeconds(),-2000*elapsed.asSeconds());
                top_right=false;
            }
            if(bot_left){
                move(2000*elapsed.asSeconds(),-2000*elapsed.asSeconds());
                as->move(-2000*elapsed.asSeconds(),2000*elapsed.asSeconds());
                bot_left=false;
            }
            if(bot_right){
                move(-2000*elapsed.asSeconds(),-2000*elapsed.asSeconds());
                as->move(2000*elapsed.asSeconds(),2000*elapsed.asSeconds());
                bot_right=false;
            }
        }
    }
}

void Statek::eventAnalysis(sf::Event& e,std::list <Obiekty*>&Asteroidy,
                   std::map <std::string,sf::Image*> Images,
                   std::map<std::string,sf::Texture*> Textures,
                   std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures){
    if((e.type==sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)||((e.type==sf::Event::KeyPressed&&e.key.code==sf::Keyboard::Space))) {
        if (Asteroidy.size()>300) return;
            Asteroidy.push_back(new Obiekty("rakieta.png",Images,Textures,beginCollisionPointsOfTextures));
            Asteroidy.back()->setPosition((int)trueCollisionPoints[13].position.x+5,  (int)trueCollisionPoints[13].position.y-50);
        }
}
