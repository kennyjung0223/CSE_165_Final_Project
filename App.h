#ifndef App_h
#define App_h

#include <vector>
#include "GlutApp.h"
#include "Rect.h"
#include "Circle.h"
#include "TexRect.h"
#include "Game.h"
#include "Sprite.h"

class App: public GlutApp {

std::vector<Shape*> shapes;
Sprite* explosion;
Game* game;

bool explosion_visible;

public:
    
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw() const;

    void keyDown(unsigned char key, float x, float y);
    void keyUp(unsigned char key, float x, float y);

    void idle();

    ~App();
};

#endif
