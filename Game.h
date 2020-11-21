#pragma once

#include <vector>
#include "Pepe.h"
#include "Sprite.h"

class Game {
    TexRect* bg;
    TexRect* fries;
    TexRect* snowball;
    Pepe* pepe;

public:
    Game();

    void draw();

    void key_up(unsigned char);
    void key_down(unsigned char);

    void idle();

    ~Game();
};