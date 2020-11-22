#pragma once

#include <vector>
#include "Pepe.h"
#include "Fries.h"
#include "Sprite.h"

class Game {
    TexRect* bg;
    TexRect* snowball;

    std::vector<TexRect*> objects;

    Pepe* pepe;

    bool movingUp = false;
    bool movingLeft = false;
    bool movingRight = false;
    bool movingDown = false;

public:
    Game();

    void draw();

    void key_up(unsigned char);
    void key_down(unsigned char);

    void update();

    void idle();

    bool collided(const TexRect&, const TexRect&) const;

    ~Game();
};