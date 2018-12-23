#include "DeltaTime.h"

int DeltaTime::getFps() {
    return DeltaTime::get().fps;
}

float DeltaTime::getDt() {
    return DeltaTime::get().deltaTime;
}

void DeltaTime::update() {
    deltaTime = deltaClock.restart().asSeconds();

    if (fpsClock.getElapsedTime().asSeconds() >= 1) {
        fps = frame;
        frame = 0;

        fpsClock.restart();
    }

    frame++;
}

DeltaTime &DeltaTime::get() {
    static DeltaTime instance;

    return instance;
}
