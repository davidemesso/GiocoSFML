#ifndef COIN_HPP_
#define COIN_HPP_

#include <SFML/Graphics.hpp> 
#include <cstdlib>
#include <string>
#include "Player.hpp"
#include "Common.hpp"


class Coin : public sf::Sprite
{
public:
    Coin() {} 
    Coin(sf::Vector2f position)
    {
        if (!texture.loadFromFile("img/coin.png"));
            texture.setSmooth(true);

        // Set fields inherited from sf::Sprite for rendering
        setTexture(texture);
        setTextureRect(sf::IntRect(0, 0, 32, 32)); 
        setScale(sf::Vector2f(1, 1)); 
        setPosition(position);
    }


    bool collect(Player& player)
    {
        if(animatingSpawn)
            return false;

        if(game::areWithinRange(*this, player, 20)) {
            player.coins++;
            return true;
        }

        return false;
    }


    bool update()
    {
        if (animatingSpawn) {
            updateAnimation();
        }

        if(expireTime-- < 0)
            return true;

        return false;
    }

private:
    void updateAnimation()
    {
        const bool updated = game::tryUpdateAnimation(
            animationTime,
            animationSpeed,
            state,
            false,
            game::Animation::VARIANT_2
        );

        if (updated) {
            setTextureRect(sf::IntRect(32 * state, 0, 32, 32));

            if (state == 0)
                animatingSpawn = false;
        }
    }


    sf::Texture texture;
    bool animatingSpawn = true;
    int state = 0;
    int expireTime = 200;
    int animationSpeed = 5;
    int animationTime = animationSpeed;
};

#endif // !COIN_HPP_