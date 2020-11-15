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
    int range = 45;
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
    } 

    void interact(shared_ptr<Entity> e)
    {
        Vector2f pos = getPosition();
        Vector2f ePos = e->getPosition();
        if(abs(pos.x-ePos.x) < range && abs(pos.y-ePos.y) < range)
            if(attacking && attackState == 1)
                e->hit();
        if (abs(pos.x-ePos.x) < 20 && abs(pos.y-ePos.y) < 20)
            life--;
    }

    void update()
    {
        if(this->life < 0) 
            setVisibility(false);
            // WILL BE GAME OVER
        Entity::update();
    } 
}; 

#endif