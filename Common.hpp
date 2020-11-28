#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <utility>
#include <SFML/Graphics.hpp>

namespace game 
{
    struct Animation {
        enum State {
            IDLE = 0,
            VARIANT_1,
            VARIANT_2,
            VARIANT_3,
        };
    };


    bool tryUpdateAnimation(
        int& animationTime,
        int animationSpeed,
        int& animationState,
        bool isIdle,
        int lastFrame = game::Animation::VARIANT_3
    );

    int updateAnimationState(int& current, bool isIdle, int lastFrame);
    bool areWithinRange(sf::Sprite& first, sf::Sprite& second, int threshold);


    template <typename Num = int>
    std::pair<Num, Num> computePositionDifference(
        sf::Sprite& first,
        sf::Sprite& second
    ) {
        const auto firstPos = first.getPosition();
        const auto secondPos = second.getPosition();

        const auto diff = firstPos - secondPos;
        return {diff.x, diff.y};
    }
}

#endif // !COMMON_HPP_