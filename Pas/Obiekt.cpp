#include <Obiekt.h>

Obiekt::Obiekt(const std::string& file,
                std::map <std::string,sf::Image*> Images,
                std::map<std::string,sf::Texture*> Textures,
                std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures) {
    toKill = false;
    beginCollisionPoints.setPrimitiveType(sf::PrimitiveType::LineStrip);
    trueCollisionPoints.setPrimitiveType(sf::PrimitiveType::LineStrip);
    loadCollisionPoints(file,Images,Textures,beginCollisionPointsOfTextures);
}

void Obiekt::loadCollisionPoints(const std::string& file,
                std::map<std::string,sf::Image*>& images,
                std::map<std::string,sf::Texture*>& txs,
                std::map<std::string,sf::VertexArray>& bcpot)
{
    std::map<std::string,sf::Image*>::const_iterator found = images.find(file);
    if(found==images.end()) {
        images.insert({file,new sf::Image()});
        images[file]->loadFromFile(file);
        for (auto i=0u; i<images[file]->getSize().x ; i++) {
            for (auto j=0u; j<images[file]->getSize().y ; j++) {
                sf::Color c = images[file]->getPixel(i,j);
                if (c.r==c.g and c.g==c.b and c.b==255) {
                    beginCollisionPoints.append(sf::Vertex(sf::Vector2f(i+getPosition().x,j+getPosition().y)));
                    trueCollisionPoints.append(sf::Vertex(sf::Vector2f(i+getPosition().x,j+getPosition().y)));
                    images[file]->setPixel(i,j,sf::Color(255,255,255,0));
                }
            }
        }
        bcpot[file]=beginCollisionPoints;
        txs[file]=new sf::Texture();
        txs[file]->loadFromImage(*images[file],sf::IntRect(0,0,images[file]->getSize().x, images[file]->getSize().y));
    } else {
        beginCollisionPoints = bcpot[file];
        trueCollisionPoints = bcpot[file];
    }
    width = images[file]->getSize().x;
    height = images[file]->getSize().y;
    setOrigin(width/2,height/2);
    setPosition(1920/2,1080/2);
    setTexture(*txs[file]);
}

float Obiekt::iloczyn_wektorowy(sf::Vector2f& A, sf::Vector2f& B, sf::Vector2f& C)
{
int x1 = C.x - A.x, y1 = C.y - A.y;
int x2 = B.x - A.x, y2 = B.y - A.y;
return x1*y2 - x2*y1;
}
void Obiekt::draw(sf::RenderWindow& window)
{
    window.draw(*this);
    //window.draw(trueCollisionPoints);
    //tu ewentualne animacje
}

bool Obiekt::isCollision(Obiekt* object )
{
    if (getGlobalBounds().intersects(object->getGlobalBounds())) {
        for (auto i=0u; i<trueCollisionPoints.getVertexCount()-1; i++) {
            int j=i+1;
            for (auto k=0u; k< object->trueCollisionPoints.getVertexCount()-1; k++) {
                int m=k+1;
                float v1 = iloczyn_wektorowy(object->trueCollisionPoints[k].position, object->trueCollisionPoints[m].position, trueCollisionPoints[i].position),
                v2 = iloczyn_wektorowy(object->trueCollisionPoints[k].position, object->trueCollisionPoints[m].position, trueCollisionPoints[j].position),
                v3 = iloczyn_wektorowy(trueCollisionPoints[i].position, trueCollisionPoints[j].position, object->trueCollisionPoints[k].position),
                v4 = iloczyn_wektorowy(trueCollisionPoints[i].position, trueCollisionPoints[j].position, object->trueCollisionPoints[m].position);
                if(((v1>0&&v2<0)||(v1<0&&v2>0)) && ( (v3>0&&v4<0)||(v3<0&&v4>0)) ) return true;
            }
        }
    }
    return false;
}
void Obiekt::animate(const sf::Time &elapsed, Statek& statek, std::list<Obiekt*>* collisionList)
{
}

void Obiekt::calcTrueCP() {
    for (unsigned i=0; i<beginCollisionPoints.getVertexCount(); i++) {
        trueCollisionPoints[i].position= getTransform().transformPoint(beginCollisionPoints[i].position);
    }
}

void Obiekt::setBounds(int left,int right,int top, int bot)
{
    this->left = left;   this->right = right;
    this->top = top;     this->bot = bot;
}

void Obiekt::bounce()
{
    sf::FloatRect przeszkoda = getGlobalBounds();
    if ((przeszkoda.left <= this->left && vel_x<0)||(przeszkoda.left+przeszkoda.width >=this->right && vel_x>0))
    {
        vel_x=-vel_x;
    }
}

void Obiekt::setSpeed(int velx,int vely, int velr)
{
    vel_r=velr;   vel_x=velx;   vel_y=vely;
}
