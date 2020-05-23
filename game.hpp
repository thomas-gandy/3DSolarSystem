#ifndef GAME_HPP
#define GAME_HPP

#include <GLFW/glfw3.h>

class Game {
public:
    void run();

private:
    void initWindow();
    void mainloop();
    void processInput();
    void cleanup();

    GLFWwindow* window;
    int WINDOW_WIDTH = 1000;
    int WINDOW_HEIGHT = 1000;
    const char* windowName = "Solar System";
};

#endif