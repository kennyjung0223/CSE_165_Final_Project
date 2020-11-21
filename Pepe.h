#pragma once

#include "TexRect.h"

class Pepe: public TexRect {
    float dx;
    float dy;
    float speed;

public:
    Pepe();

    void key_up(unsigned char);
    void key_down(unsigned char);
    float get_speed() const;

    void increment_speed();

    void idle();

};