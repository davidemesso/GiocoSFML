#ifndef PLAYER
#define PLAYER 

// g++ Game.cpp -lsfml-graphics -lsfml-window -lsfml-system
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp> 
#include "Entity.cpp"
#include <memory>

using namespace sf;
using namespace std;

class Player : public Entity
{
private:
    int range = 50;
public:
    int coins = 0;
    // INHERITED ENTITY FIELDS 
    // Inventory inventory

    Player() {};

    Player(string name, float life, float attack, string file, Vector2f position = Vector2f(0,0)) 
        : Entity(name, life, attack, file, position)
    {
        attackSpeed = 20;
        speed = 3;
        atk = 10;
        redBlinking = 50;
        deathOffset = 8;
    } 

    void interact(shared_ptr<Entity> e)
    {
        Vector2f pos = getPosition();
        Vector2f ePos = e->getPosition();
        if(abs(pos.x-ePos.x) < range && abs(pos.y-ePos.y) < range)
            if(attacking && attackState == 1)
                e->hit(true, atk);
        if (abs(pos.x-ePos.x) < 20 && abs(pos.y-ePos.y) < 20)
            hit(false, e->atk);
    }

    void update()
    {
        if(life <= 0)
        {
            setScale(10,10);
            //end game
        }
        Entity::update();
    } 
}; 

#endif