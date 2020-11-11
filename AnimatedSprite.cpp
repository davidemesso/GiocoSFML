#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp> 

using namespace sf;
using namespace std;

class AnimatedSprite : public sf::Sprite
{
private:
    Texture texture;
    bool visible = true;

public:
    int state = 0;
    int animationSpeed = 25;
    int animationTime = animationSpeed;

public:
    AnimatedSprite(string file)
    {
        initRendering(file);
    }

    void initRendering(string file)
    {
        if (!texture.loadFromFile(file));
            texture.setSmooth(true);

        // Set fields inherited from sf::Sprite for rendering
        setTexture(texture);
        setTextureRect(IntRect(0, 0, 32, 32)); // Sprite 32x32 in first position
        setScale(Vector2f(2, 2)); 
        setPosition(Vector2f(10, 10));
    }

    void setVisibility(bool visible)
    {
        this->visible = visible;
    }

    bool isVisible()
    {
        return visible;
    }

    // For future custom drawing function
    // void draw(sf::RenderTarget &window, sf::RenderStates states) const 
    // {
    //     window.draw(*this);
    // }

    void update()
    {
        if(!animationTime--)
        {
            state = (state+1) % 3;
            setTextureRect(IntRect(32 * state, 0, 32, 32));
            animationTime = animationSpeed;
        }
    } 
};