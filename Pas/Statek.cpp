#include <Statek.h>
#include <iostream>

Statek::Statek(const std::string& file,
       std::map <std::string,sf::Image*>Images,
       std::map<std::string,sf::Texture*> Textures,
       std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures) : Obiekt(file,Images,Textures,beginCollisionPointsOfTextures)
{
}

void Statek::draw(sf::RenderWindow& window) {
    window.draw(*this);
    //window.draw(trueCollisionPoints);
    //tu ewentualne animacje
}
void Statek::animate(const sf::Time &elapsed, Statek& statek, std::list<Obiekt*>* collisionList)
{
}
void Statek::animate(sf::Time elapsed,std::map<int,bool>& status,std::list <Obiekt*> &Obiekty) {
    sf::FloatRect statek = getGlobalBounds();
    if(status[sf::Keyboard::D]&&this->right>=statek.left+statek.width) {
        if(reverse){
            setSpeed(-100,0,0);
            move((vel_x-boost)*elapsed.asSeconds(),vel_y*elapsed.asSeconds());
            if(boost<100)boost++;
        }
        else {
            setSpeed(100,0,0);
            move((vel_x+boost)*elapsed.asSeconds(),vel_y*elapsed.asSeconds());
            if(boost<100)boost++;
        }
    }
    if(status[sf::Keyboard::A]&&this->left<=statek.left) {
        if(reverse){
            setSpeed(100,0,0);
            move((vel_x+boost)*elapsed.asSeconds(),vel_y*elapsed.asSeconds());
            if(boost<100)boost++;
        }
        else {
            setSpeed(-100,0,0);
            move((vel_x-boost)*elapsed.asSeconds(),vel_y*elapsed.asSeconds());
            if(boost<100)boost++;
        }
    }
    if(status[sf::Keyboard::W]&&this->top<=statek.top) {
        if(reverse){
            setSpeed(0,100,0);
            move(vel_x*elapsed.asSeconds(),(vel_y+boost)*elapsed.asSeconds());
            if(boost<100)boost++;
        }
        else{
            setSpeed(0,-100,0);
            move(vel_x*elapsed.asSeconds(),(vel_y-boost)*elapsed.asSeconds());
            if(boost<100)boost++;
        }
    }
    if(status[sf::Keyboard::S]&&this->bot>=statek.top+statek.height) {
        if(reverse){
            setSpeed(0,-100,0);
            move(vel_x*elapsed.asSeconds(),(vel_y-boost)*elapsed.asSeconds());
            if(boost<100)boost++;
        }
        else {
            setSpeed(0,100,0);
            move(vel_x*elapsed.asSeconds(),(vel_y+boost)*elapsed.asSeconds());
            if(boost<100)boost++;
        }
    }
    if(!(status[sf::Keyboard::S]||status[sf::Keyboard::W]||status[sf::Keyboard::A]||status[sf::Keyboard::D])){
        boost=0;
    }
    calcTrueCP();
    for (auto obj : Obiekty) {
        if (isCollision(obj)) {
            if(dynamic_cast<Powerup*>(obj)){
                if(dynamic_cast<Powerup*>(obj)->nr==1){
                    reverse=true;
                }
                obj->toKill=true;
            }
            else{
                if(top_right&&bot_right){
                    move(-300*elapsed.asSeconds(),0);
                    obj->setSpeed(150,0,0);
                }
                if(top_left&&top_right){
                    move(0,300*elapsed.asSeconds());
                    obj->setSpeed(0,-150,-30);
                }
                if(top_left&&bot_left){
                    move(300*elapsed.asSeconds(),0);
                    obj->setSpeed(-150,0,0);
                }
                if(bot_right&&bot_left){
                    move(0,-300*elapsed.asSeconds());
                    obj->setSpeed(0,150,0);
                }
                if(top_left){
                    move(300*elapsed.asSeconds(),300*elapsed.asSeconds());
                    obj->setSpeed(-150,-150,-30);
                }
                if(top_right){
                    move(-300*elapsed.asSeconds(),300*elapsed.asSeconds());
                    obj->setSpeed(150,-150,-30);
                }
                if(bot_left){
                    move(300*elapsed.asSeconds(),-300*elapsed.asSeconds());
                    obj->setSpeed(-150,150,30);
                }
                if(bot_right){
                    move(-300*elapsed.asSeconds(),-300*elapsed.asSeconds());
                    obj->setSpeed(150,150,30);
                }
                top_right=false;
                bot_right=false;
                top_left=false;
                bot_left=false;
            }
        }
    }
}

void Statek::eventAnalysis(sf::Event& e,std::list <Obiekt*>&kontener,
                   std::map <std::string,sf::Image*> Images,
                   std::map<std::string,sf::Texture*> Textures,
                   std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures){
    if((e.type==sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)||((e.type==sf::Event::KeyPressed&&e.key.code==sf::Keyboard::Space))) {
        if (kontener.size()>300||rakiet>=rocketlimit) return;
            kontener.push_back(new Rakieta("rakieta3.png",Images,Textures,beginCollisionPointsOfTextures));
            kontener.back()->setPosition((int)trueCollisionPoints[1000].position.x+20,(int)trueCollisionPoints[1000].position.y-100);
            rakiet++;
        }
}
