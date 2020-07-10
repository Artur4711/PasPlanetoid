#include <Obiekt.h>
#include <Statek.h>
#include <Asteroida.h>
#include <Powerup.h>
#include <Rakieta.h>

void ustaw_przeszkody(std::map <std::string,sf::Image*> &Images,
                      std::map<std::string,sf::Texture*> &Textures,
                      std::map<std::string,sf::VertexArray> &beginCollisionPointsOfTextures,
                      std::list <Obiekt*> &Obiekty,
                      sf::VertexArray &Gwiazdy, int WIDTH, int HEIGHT);

Statek ustaw_statek(std::map <std::string,sf::Image*> &Images,
                    std::map<std::string,sf::Texture*> &Textures,
                    std::map<std::string,sf::VertexArray> &beginCollisionPointsOfTextures,
                    int WIDTH, int HEIGHT);

void kolizje(Statek &kosmiczny,std::list <Obiekt*> &Asteroidy);

int main()
{
    int HEIGHT=1080;
    int WIDTH=1920;

    std::map <std::string,sf::Image*> Images;
    std::map<std::string,sf::Texture*> Textures;
    std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures;
    std::list <Obiekt*> Obiekty;
    sf::VertexArray Gwiazdy(sf::PrimitiveType::Points,2000);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pas planetoid");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);
    window.setPosition(sf::Vector2i(0,0));

    sf::Clock Rclock;
    sf::Clock clock;
    sf::Clock reverseclock;
    std::map<int,bool> status;

    ustaw_przeszkody(Images,Textures,beginCollisionPointsOfTextures,Obiekty,Gwiazdy,WIDTH,HEIGHT);
    auto kosmiczny = ustaw_statek(Images,Textures,beginCollisionPointsOfTextures,WIDTH,HEIGHT);

    sf::Event event;
    while (window.isOpen()) {

    //EVENTS
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )) window.close();
            if (event.type==sf::Event::KeyPressed) status[event.key.code]=true;
            if (event.type==sf::Event::KeyReleased)status[event.key.code]=false;
            kosmiczny.eventAnalysis(event,Obiekty,Images,Textures,beginCollisionPointsOfTextures);
        }

    //LOGIC
        sf::Time elapsed = clock.restart();
        window.clear(sf::Color(20,20,50));
        kolizje(kosmiczny,Obiekty);
        kosmiczny.animate(elapsed,status,Obiekty);
        for(auto i=0; i<Gwiazdy.getVertexCount();i++)
        {
            Gwiazdy[i].position.y+=1;
            if(Gwiazdy[i].position.y>HEIGHT)
            {
                Gwiazdy[i].position.y=0;
            }
        }
        if(kosmiczny.reverse){
            if(Rclock.getElapsedTime().asSeconds()>5){
                kosmiczny.reverse=false;
            }
        }
        else Rclock.restart();


    //DRAW
        window.draw(Gwiazdy);
        auto obj = Obiekty.begin();
        while (obj!=Obiekty.end()) {
            Obiekt* obiekt = *obj;
            obiekt->animate(elapsed,kosmiczny,&Obiekty);
            if (obiekt->isDead()||obiekt->getPosition().y>HEIGHT) {
                delete obiekt;
                obj = Obiekty.erase(obj);
            }
            else {
                window.draw(*obiekt);
                obj++;
            }
        }
        kosmiczny.draw(window);
        window.display();
    }

    return 0;
}
void ustaw_przeszkody(std::map <std::string,sf::Image*> &Images,
                    std::map<std::string,sf::Texture*> &Textures,
                    std::map<std::string,sf::VertexArray> &beginCollisionPointsOfTextures,
                    std::list <Obiekt*> &Obiekty,
                    sf::VertexArray &Gwiazdy, int WIDTH, int HEIGHT)
{
    for (int j=0; j<50; j++) {
        for (int i=0; i<3; i++) {
            Obiekty.push_back(new Asteroida("asteroida.png",Images,Textures,beginCollisionPointsOfTextures));
            Obiekty.back()->setBounds(0,WIDTH,0,HEIGHT);
            Obiekty.back()->setPosition(-50+std::rand()%(HEIGHT+100),-200*j+100*i );
            if(rand()%15==7){
                Obiekty.push_back(new Powerup("powerup.png",Images,Textures,beginCollisionPointsOfTextures));
                Obiekty.back()->setPosition(-50+std::rand()%(HEIGHT+100),-200*j+100*i);
            }

        }
    }
    //gwiazdy w tle
    for (auto i = 0u; i<Gwiazdy.getVertexCount(); i++) {
        Gwiazdy[i].position = sf::Vector2f(rand()%WIDTH,rand()%HEIGHT);
        Gwiazdy[i].color = sf::Color(rand()%156+100,rand()%156+100,rand()%156+100,255);
    }
}

Statek ustaw_statek(std::map <std::string,sf::Image*> &Images,
                    std::map<std::string,sf::Texture*> &Textures,
                    std::map<std::string,sf::VertexArray> &beginCollisionPointsOfTextures,
                    int WIDTH, int HEIGHT)
{
    Statek statek("statek2.png",Images, Textures,beginCollisionPointsOfTextures);
    statek.setPosition(WIDTH/2,HEIGHT-100);
    statek.setScale(0.1,0.1);
    statek.setBounds(0,WIDTH,0,HEIGHT);
    return statek;
}

void kolizje(Statek &kosmiczny,std::list <Obiekt*> &Asteroidy) //służy tylko do odpowiedzi na udeżenie
{
    sf::FloatRect statek_b = kosmiczny.getGlobalBounds();
    for (auto as : Asteroidy){
        sf::FloatRect asteroida = as->getGlobalBounds();
        if (statek_b.top >= asteroida.top && statek_b.top <= asteroida.top+asteroida.height &&
            statek_b.left >= asteroida.left && statek_b.left <= asteroida.left+asteroida.width)
        {
            kosmiczny.top_left=true;
        }
        if (statek_b.top >= asteroida.top && statek_b.top <= asteroida.top+asteroida.height &&
            statek_b.left+statek_b.width >= asteroida.left && statek_b.left+statek_b.width<=asteroida.left+asteroida.width)
        {
            kosmiczny.top_right=true;
        }
        if (statek_b.top+statek_b.height >= asteroida.top && statek_b.top+statek_b.height <= asteroida.top+asteroida.height &&
            statek_b.left >= asteroida.left && statek_b.left <= asteroida.left+asteroida.width)
        {
            kosmiczny.bot_left=true;
        }
        if (statek_b.top+statek_b.height >= asteroida.top && statek_b.top+statek_b.height <= asteroida.top+asteroida.height &&
            statek_b.left+statek_b.width >= asteroida.left && statek_b.left+statek_b.width<=asteroida.left+asteroida.width)
        {
            kosmiczny.bot_right=true;
        }
    }
}
