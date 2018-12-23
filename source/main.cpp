#include "GameManager.h"

int main() {
    std::srand(std::time(0));

    GameManager manager(1366, 768, "Santa Fight");
    manager.runGame();

    return 0;
}