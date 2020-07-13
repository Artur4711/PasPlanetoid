#include <Obiekt.h>
#include <Statek.h>


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
    bool boss=false;
    bool end=false;

    std::map <std::string,sf::Image*> Images;
    std::map<std::string,sf::Texture*> Textures;
    std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures;
    std::list <Obiekt*> Obiekty;
    std::list <sf::RectangleShape*> Rakiety;
    sf::VertexArray Gwiazdy(sf::PrimitiveType::Points,2000);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pas planetoid", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);
    window.setPosition(sf::Vector2i(0,0));
    window.setMouseCursorVisible(false);

    sf::Clock clock;
    sf::Clock Speedupclock;
    sf::Clock Reloadclock;
    sf::Clock Reverseclock;
    std::map<int,bool> status;

    ustaw_przeszkody(Images,Textures,beginCollisionPointsOfTextures,Obiekty,Gwiazdy,WIDTH,HEIGHT);
    auto kosmiczny = ustaw_statek(Images,Textures,beginCollisionPointsOfTextures,WIDTH,HEIGHT);

    sf::Event event;
    while (window.isOpen()&&kosmiczny.hp>0&&!end) {

    //EVENTS
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )) window.close();
            if (event.type==sf::Event::KeyPressed) status[event.key.code]=true;
            if (event.type==sf::Event::KeyReleased)status[event.key.code]=false;
            kosmiczny.eventAnalysis(event,Obiekty,Images,Textures,beginCollisionPointsOfTextures);
        }

    //LOGIC
        if (kosmiczny.shoot){
            Obiekty.push_back(new Asteroida("asteroida.png",Images,Textures,beginCollisionPointsOfTextures));
            Obiekty.back()->setBounds(0,WIDTH,0,HEIGHT);
            Obiekty.back()->setScale(0.6,0.6);
            Obiekty.back()->setPosition(kosmiczny.posBoss.x-550,kosmiczny.posBoss.y-300);
            Obiekty.back()->setSpeed(0,200,0);
            Obiekty.push_back(new Asteroida("asteroida.png",Images,Textures,beginCollisionPointsOfTextures));
            Obiekty.back()->setBounds(0,WIDTH,0,HEIGHT);
            Obiekty.back()->setScale(0.5,0.5);
            Obiekty.back()->setPosition(kosmiczny.posBoss.x-900,kosmiczny.posBoss.y-380);
            Obiekty.back()->setSpeed(0,200,0);
            Obiekty.push_back(new Asteroida("asteroida.png",Images,Textures,beginCollisionPointsOfTextures));
            Obiekty.back()->setBounds(0,WIDTH,0,HEIGHT);
            Obiekty.back()->setScale(0.5,0.5);
            Obiekty.back()->setPosition(kosmiczny.posBoss.x-100,kosmiczny.posBoss.y-380);
            Obiekty.back()->setSpeed(0,200,0);
        }
        if(Obiekty.size()<=5&&boss==false){
            Obiekty.push_back(new Boss("boss.png",Images, Textures, beginCollisionPointsOfTextures));
            Obiekty.back()->setPosition(WIDTH/2,200);
            Obiekty.back()->setBounds(0,WIDTH,0,HEIGHT);
            boss=true;
        }
        if(boss==true&&kosmiczny.bosshp<=0){
                  end=true;
                  Obiekty.clear();
                  std::cout<<"Wygrana"<<std::endl;
        }
        sf::Time elapsed = clock.restart();
        window.clear(sf::Color(20,20,50));
        kolizje(kosmiczny,Obiekty);
        kosmiczny.animate(elapsed,status,Obiekty);
        for(auto i=0; i<Gwiazdy.getVertexCount();i++)
        {
            if(kosmiczny.speedup)Gwiazdy[i].position.y+=3;
            else Gwiazdy[i].position.y++;
            if(Gwiazdy[i].position.y>HEIGHT)
            {
                Gwiazdy[i].position.y=0;
            }
        }
        if(kosmiczny.reverse){
            if(Reverseclock.getElapsedTime().asSeconds()>5){
                kosmiczny.reverse=false;
            }
        }
        else Reverseclock.restart();
        if(kosmiczny.speedup){
            if(Speedupclock.getElapsedTime().asSeconds()>10){
                kosmiczny.speedup=false;
            }
        }
        else Speedupclock.restart();
        if(Reloadclock.getElapsedTime().asSeconds()>1&&kosmiczny.rakiet>0){
            kosmiczny.rakiet--;
            kosmiczny.booster+=2;
            Reloadclock.restart();
        }
        if(kosmiczny.rakiet==0&&Reloadclock.getElapsedTime().asSeconds()>1){
            kosmiczny.booster+=2;
            Reloadclock.restart();
        }
        sf::RectangleShape HP(sf::Vector2f(kosmiczny.hp,30));
        HP.setFillColor(sf::Color::Yellow);
        HP.setPosition(0,HEIGHT-30);
        sf::RectangleShape HPfull(sf::Vector2f(300,30));
        HPfull.setPosition(0,HEIGHT-30);
        HPfull.setFillColor(sf::Color::Magenta);
        for(int i=0;i<kosmiczny.rocketlimit;i++){
            Rakiety.push_back(new sf::RectangleShape(sf::Vector2f(30,70)));
            Rakiety.back()->setFillColor(sf::Color::Blue);
            Rakiety.back()->setPosition(WIDTH-50-(i*50),HEIGHT-50);
        }
            for(int i=0;i<kosmiczny.rakiet;i++){
                Rakiety.push_back(new sf::RectangleShape(sf::Vector2f(30,70)));
                Rakiety.back()->setFillColor(sf::Color::Red);
                Rakiety.back()->setPosition(WIDTH-50-(i*50),HEIGHT-50);
            }



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
        for (auto el:Rakiety){
            window.draw(*el);
        }
        if(boss==true){
            sf::RectangleShape HPboss(sf::Vector2f(kosmiczny.bosshp,30));
            HPboss.setFillColor(sf::Color::Cyan);
            HPboss.setPosition(500,30);
            sf::RectangleShape HPbossfull(sf::Vector2f(900,30));
            HPbossfull.setFillColor(sf::Color::Magenta);
            HPbossfull.setPosition(500,30);
            window.draw(HPbossfull);
            if(kosmiczny.bosshp>0){
                window.draw(HPboss);
            }
        }
        window.draw(HPfull);
        window.draw(HP);
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
    for (int j=0; j<40; j++) {
        for (int i=0; i<3; i++) {
            Obiekty.push_back(new Asteroida("asteroida.png",Images,Textures,beginCollisionPointsOfTextures));
            Obiekty.back()->setBounds(0,WIDTH,0,HEIGHT);
            Obiekty.back()->setPosition(-50+std::rand()%(HEIGHT+100),-350*j+100*i );
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
