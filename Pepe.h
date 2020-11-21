#pragma once

#include "TexRect.h"

class Pepe: public TexRect {
    float speed;

public:
    Pepe();

    void moveUp();
    void moveLeft();
    void moveRight();
    void moveDown();

    float get_speed() const;

    void increment_speed();

    void idle();

};