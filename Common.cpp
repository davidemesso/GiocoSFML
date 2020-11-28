#include "Common.hpp"

using namespace std;
using namespace sf;


namespace game 
{
    bool tryUpdateAnimation(
        int& animationTime,
        int animationSpeed,
        int& animationState,
        bool isIdle,
        int lastFrame
    ) {
        const bool shouldUpdate = animationTime-- == 0;
        if (!shouldUpdate)
            return false;

        animationTime = animationSpeed;
        updateAnimationState(
            animationState,
            isIdle,
            lastFrame
        );

        return true;
    }


    int updateAnimationState(int& current, bool isIdle, int lastFrame)
    {
        return current = isIdle
            ? Animation::IDLE
            : ++current % lastFrame;
    }


    bool areWithinRange(Sprite& first, Sprite& second, int threshold)
    {
        const auto [x, y] =
            computePositionDifference(first, second);

        return 
            abs(x) < threshold && 
            abs(y) < threshold;
    }
}