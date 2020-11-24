#pragma once

#include <vector>
#include "Pepe.h"
#include "Projectiles.h"
#include "Sprite.h"

class Game {
    TexRect* bg;
    Sprite* explosion;

    std::vector<TexRect*> snowballs;
    std::vector<TexRect*> apples;
    std::vector<float> starting_points;

    Pepe* pepe;
    TexRect* fainted_pepe;

    bool movingUp = false;
    bool movingLeft = false;
    bool movingRight = false;
    bool movingDown = false;

    bool home;
    bool gameover;

    int score;
    int temp;
    const int A_QUANTITY = 3;
    int sb_quantity;

    int high_score;
    float index;
    int i;

    bool explosion_visible;

    int get_high_score(int);

public:

    Game();

    void draw();
    void draw_snowballs();
    void draw_apples();

    void key_up(unsigned char);
    void key_down(unsigned char);

    void update();

    int score_threshold(int);
    void check_threshold();

    void generate_apples();
    void generate_snowballs();
    void add_snowball();

    void reset_sp();
    void reset();

    void explode();

    bool collided(const TexRect&, const TexRect&) const;
    bool is_gameover() const;

    void renderText(std::string, float, float, void*, float, float, float);

    void idle();

    ~Game();
};