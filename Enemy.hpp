#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include <cstdlib>
#include <string>
#include <SFML/Graphics.hpp> 
#include "Entity.hpp"
#include "Player.hpp"
#include <random>
#include "Common.hpp"


class Enemy : public Entity
{
private:
    Player* target;

public:
    Enemy() {};
    Enemy(
        std::string name, 
        float life, 
        float attack, 
        std::string file, 
        Player* target, 
        sf::Vector2f position = sf::Vector2f(0,0)
    ) : 
        Entity(name, life, attack, file, position)
    {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 200);

        setPosition(distr(gen), distr(gen));
        this->target = target;
        speed = 0.7;
        this->atk = attack;
    }


    void update()
    {
        const auto [x, y] =
            game::computePositionDifference(*target, *this);

        const auto speedX = (x != 0 ? (x / abs(x)) : 0);
        const auto speedY = (y != 0 ? (y / abs(y)) : 0);

        velocity = sf::Vector2f(speedX, speedY);
        Entity::update();
    } 
}; 

#endif // !ENEMY_HPP_