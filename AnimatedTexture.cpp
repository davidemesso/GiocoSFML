#include <stdlib.h>
#include <SFML/Graphics.hpp> 

using namespace sf;
using namespace std;

class AnimatedSprite : public sf::Sprite
{
private:
    Texture texture;
    int state = 0;

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

    void update()
    {
        state = state++ % 3;
        setTextureRect(IntRect(0 * state, 0, 32, 32));
    } 
};