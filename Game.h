#pragma once

#include <vector>
#include "Pepe.h"
#include "Sprite.h"

class Game {
    TexRect* bg;
    TexRect* fries;
    TexRect* snowball;

    std::vector<Rect*> objects;

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

    bool collided(const Rect&, const Rect&) const;

    ~Game();
};