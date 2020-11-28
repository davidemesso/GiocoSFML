#ifndef PLAYER_HPP_
#define PLAYER_HPP_ 

// g++ Game.cpp -lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp> 
#include <cstdlib>
#include <string>
#include "Entity.hpp"
#include <memory>


class Player : public Entity
{
private:
    int range = 50;
public:
    int coins = 0;

    Player() {};
    Player(
        std::string name, 
        float life, 
        float attack, 
        std::string file, 
        sf::Vector2f position = sf::Vector2f(0, 0)
    ) : 
        Entity(name, life, attack, file, position)
    {
        attackSpeed = 20;
        speed = 3;    
        atk = 10;
        redBlinking = 50;
        deathOffset = 8;
    }


    void interact(std::shared_ptr<Entity> e)
    {
        auto pos = getPosition();
        auto ePos = e->getPosition();

        if(abs(pos.x-ePos.x) < range && abs(pos.y-ePos.y) < range)
            if(attacking && attackState == 1)
                e->hit(true, atk);

        if (abs(pos.x-ePos.x) < 20 && abs(pos.y-ePos.y) < 20)
            hit(false, e->atk);
    }


    bool update()
    {
        bool ret = true;
        Entity::update();
        if(life <= 0)
        {
            setScale(10, 10);
            if(!animatingDeath)
                ret = false;
        }
        return ret;
    }
};

#endif // !PLAYER_HPP_