#ifndef ENTITY
#define ENTITY 

#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp> 
#include "AnimatedSprite.cpp"

using namespace sf;
using namespace std;

class Entity : public AnimatedSprite
{
public:
    string name; 
    float atk; 
    float life;
    Sprite sprite;
    float speed;
    
    Entity(){};

    Entity(string name, float life, float attack, string file, Vector2f position = Vector2f(0,0)) 
        : AnimatedSprite(file, position)
    {
        this->name = name; 
        this->life = life; 
        this->atk  = atk; 
    } 

    Vector2f getVelocity()
    {
        return velocity;
    }

    void setVelocity(float x, float y)
    {
        velocity = Vector2f(x, y);
    }

    void resetVelocityX()
    {
        velocity.x = 0;
    }

    void resetVelocityY()
    {
        velocity.y = 0;
    }

    void update()
    {
        AnimatedSprite::update();
        move(velocity.x * speed, velocity.y * speed);
    } 
}; 

#endif  