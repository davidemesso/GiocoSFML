#ifndef ANIMATED_SPRITE_HPP_
#define ANIMATED_SPRITE_HPP_

#include <cstdlib>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Common.hpp"


class AnimatedSprite : public sf::Sprite
{
private:
    sf::Texture texture;
    bool visible = true;
    bool idle = true;

public:
    int walkState = 0;
    int attackState = 0;
    int animationSpeed = 10;
    int animationTime = animationSpeed;
    int attackSpeed = 50;
    int attackCooldown = attackSpeed;
    int attackMaxTime = 10;
    int attackTime = attackMaxTime;
    int yOffset = 0;
    bool attacking = false;
    bool animatingDeath = false;
    sf::Vector2f velocity = {0, 0};


    AnimatedSprite() {};
    AnimatedSprite(
        std::string file, 
        sf::Vector2f position = {0, 0}
    ) {
        initRendering(file);
        setPosition(position);
    }
    

    void setVisibility(bool visible) {  
        this->visible = visible;
    }

    bool isVisible() {
        return visible;
    }


    void initRendering(std::string file)
    {
        if (!texture.loadFromFile(file));
            texture.setSmooth(true);

        // Set fields inherited from sf::Sprite for rendering
        setTexture(texture);
        setTextureRect(sf::IntRect(0, 0, 16, 32)); // Sprite 16x32 in first position
        setScale(sf::Vector2f(2, 2)); 
        setPosition(sf::Vector2f(10, 10));
    }


    void animate()
    {
        if(animatingDeath)
            return;

        if(velocity.x == 0)
        {
            if(velocity.y == 1)
                yOffset = 0;

            else if(velocity.y == -1)
                yOffset = 2;
        }

        if(velocity.y == 0)
        {
            if(velocity.x == 1)
                yOffset = 1;

            else if(velocity.x == -1)
                yOffset = 3;
        }

        const int attackOffset = attacking ? 4 : 0;
        const int currentState = attacking ? attackState : walkState;

        setTextureRect({
            16 * currentState,
            32 * (yOffset + attackOffset),
            16, 32
        });
    
        idle = velocity == sf::Vector2f(0, 0);
    }


    void update()
    {
        const bool shouldAnimate = 
            tryUpdateWalkAnimation() ||
            tryUpdateAttackAnimation();

        if (shouldAnimate)
            animate();
    }


    void draws(sf::RenderTarget& window)
    {
        if (isVisible())
            window.draw(*this);
    }

private:
    bool tryUpdateWalkAnimation() 
    {
        return game::tryUpdateAnimation(
            animationTime,
            animationSpeed,
            walkState,
            idle
        );
    }

    bool tryUpdateAttackAnimation()
    {
        if(attacking) {
            velocity = {0, 0};
        }

        return game::tryUpdateAnimation(
            attackTime,
            attackSpeed,
            attackState,
            !attacking
        );
    }
};

#endif // !ANIMATED_SPRITE_HPP_