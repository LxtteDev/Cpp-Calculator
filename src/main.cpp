#include <iostream>
#include "window/window.h"

int main() {
    std::cout << "Starting window" << std::endl;

    Window* window = new Window("Calculator", 385, 425);

    bool running = true;
    while (running) {
        if (!window->proccessMessages()) {
            std::cout << "Closing window" << std::endl;
            running = false;
        }

        Sleep(10);
    }

    delete window;

    return 0;
}