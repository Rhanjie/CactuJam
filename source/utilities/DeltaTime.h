#ifndef IZOGAME_DELTATIME_H
#define IZOGAME_DELTATIME_H

#include <SFML/System/Clock.hpp>

class DeltaTime {
public:
    void update();

    static int getFps();
    static float getDt();

    DeltaTime(const DeltaTime&) = delete;
    DeltaTime& operator = (const DeltaTime&) = delete;

    static DeltaTime& get();

private:
    sf::Clock fpsClock;
    sf::Clock deltaClock;

    unsigned int frame = 0;
    unsigned int fps   = 0;
    float deltaTime    = 0;

    DeltaTime() {}
   ~DeltaTime() {}
};

#endif //IZOGAME_DELTATIME_H
