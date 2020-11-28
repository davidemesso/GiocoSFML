#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <cstdlib>
#include <string>
#include <SFML/Graphics.hpp> 
#include "AnimatedSprite.hpp"


class Entity : public AnimatedSprite
{
private:
    int redTime = 0;
    int deathState = 0;
    int deathTime = 40;

public:
    int redBlinking = 20;
    int deathOffset = 4;
    std::string name; 
    float atk; 
    float life;
    sf::Sprite sprite;
    float speed;
    

    Entity(){};
    Entity(
        std::string name, 
        float life, 
        float attack, 
        std::string file, 
        sf::Vector2f position = sf::Vector2f(0,0)
    ) : 
        AnimatedSprite(file, position),
        name(name),
        life(life),
        atk(atk)
    {}


    sf::Vector2f getVelocity() {
        return velocity;
    }

    void setVelocity(float x, float y) {
        velocity = sf::Vector2f(x, y);
    }

    void resetVelocityX() {
        velocity.x = 0;
    }

    void resetVelocityY() {
        velocity.y = 0;
    }


    void hit(bool knockback, int damage)
    {
        if(!redTime)
        {
            setColor(sf::Color::Red);
            redTime = redBlinking;
            life -= damage;
        }

        if(knockback)
            move(-velocity.x * 1.5, -velocity.y * 1.5);
    }


    void update()
    {
        if(life <= 0)
            animatingDeath = true;

        if(animatingDeath)
        {
            if(!deathTime--)
            {
                setColor(sf::Color::White);
                setTextureRect(sf::IntRect(deathState * 16, 32 * deathOffset, 16, 32));
                deathState++;
                if(deathState == 4)
                {
                    setVisibility(false);
                    animatingDeath = false;
                }
                deathTime = 5;
            }
            return;
        }

        if(redTime > 0)
            redTime--;
        else 
            setColor(sf::Color::White);

        AnimatedSprite::update();
        move(velocity.x * speed, velocity.y * speed);
    }
}; 

#endif // !ENTITY_HPP_