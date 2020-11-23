#pragma once

#include <vector>
#include "Pepe.h"
#include "Projectiles.h"
#include "Sprite.h"

class Game {
    TexRect* bg;
    Sprite* explosion;

    std::vector<TexRect*> apples;
    std::vector<TexRect*> snowballs;

    Pepe* pepe;

    bool movingUp = false;
    bool movingLeft = false;
    bool movingRight = false;
    bool movingDown = false;

    bool gameover;

    int score;
    int temp;
    const int A_QUANTITY = 3;
    int sb_quantity;

    int high_score;

    int get_high_score(int);

public:

    bool explosion_visible;

    Game();

    void draw();
    void draw_snowballs();
    void draw_apples();

    void key_up(unsigned char);
    void key_down(unsigned char);

    void update();

    void generate_apples();
    void generate_snowballs();

    void idle();

    void reset();

    void explode();

    bool collided(const TexRect&, const TexRect&) const;
    bool is_gameover() const;

    void renderText(std::string, float, float, void*, float, float, float);

    ~Game();
};