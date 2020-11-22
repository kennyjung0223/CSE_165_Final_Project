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
    
Game* game;

public:
    
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw() const;

    void keyDown(unsigned char key, float x, float y);
    void keyUp(unsigned char key, float x, float y);

    void idle();

    friend void explosion_timer(int);
    friend void snowballs_timer(int);

    ~App();
};

#endif
