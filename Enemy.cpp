#ifndef ENEMY
#define ENEMY

#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp> 
#include "Entity.cpp"
#include "Player.cpp"
#include <random>

using namespace sf;
using namespace std;

class Enemy : public Entity
{
private:
    Player* target;

public:

    Enemy(string name, float life, float attack, string file, Player* target, Vector2f position = Vector2f(0,0)) 
        : Entity(name, life, attack, file, position)
    {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 200);

        setPosition(distr(gen), distr(gen));
        this->target = target;
        speed = 0.5;
    } 

    void update()
    {
        Vector2f pos = getPosition();
        Vector2f tarPos = target->getPosition();
     
        int x = pos.x - tarPos.x;
        int y = pos.y - tarPos.y;
        if(x != 0 && y != 0)
            velocity = Vector2f(-(x / abs(x)), - (y / abs(y)));

        Entity::update();
    } 
}; 

#endif