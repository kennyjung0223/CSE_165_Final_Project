#pragma once

#include <vector>
#include "Pepe.h"
#include "Projectiles.h"
#include "Sprite.h"

class Game {
    TexRect* bg;
    Sprite* explosion;

    std::vector<TexRect*> fries;
    std::vector<TexRect*> snowballs;

    Pepe* pepe;

    bool movingUp = false;
    bool movingLeft = false;
    bool movingRight = false;
    bool movingDown = false;

    bool gameover;
    bool explosion_visible;

    int score;

public:

    Game();

    void draw();
    void draw_snowballs();
    void draw_fries();

    void key_up(unsigned char);
    void key_down(unsigned char);

    void update();

    void generate_snowballs();

    void idle();

    Sprite* get_explosion() const;

    bool collided(const TexRect&, const TexRect&) const;
    bool is_gameover() const;
    
    bool is_explosion_visible() const;
    void set_explosion_off();

    void renderText(std::string, float, float, void*, float, float, float);

    ~Game();
};