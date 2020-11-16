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
private:
    int redTime = 0;
    int deathState = 0;
    int deathTime = 40;
public:
    int redBlinking = 20;
    int deathOffset = 4;
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

    void hit(bool knockback, int damage)
    {
        if(!redTime)
        {
            setColor(Color::Red);
            redTime = redBlinking;
            life-=damage;
        }
        if(knockback)
            move(-velocity.x * 1.5, -velocity.y * 1.5);
    }

    void update()
    {

        if(life<=0)
            animatingDeath = true;
        if(animatingDeath )
        {
            if(!deathTime--)
            {
                setColor(Color::White);
                setTextureRect(IntRect(deathState * 16, 32 * deathOffset, 16, 32));
                deathState++;
                if(deathState == 4)
                    setVisibility(false);
                deathTime = 5;
            }
            return;
        }

        if(redTime > 0)
            redTime--;
        else 
            setColor(Color::White);
        AnimatedSprite::update();
        move(velocity.x * speed, velocity.y * speed);
    } 
}; 

#endif  