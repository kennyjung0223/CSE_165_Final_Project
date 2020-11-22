#include "Fries.h"
#include <time.h>
#include <iostream>

Fries::Fries(): TexRect("assets/fries.png", 0, 1.0, 0.1, 0.1) {
    srand(time(NULL));

    x_speed = ((rand() % 10) / 1125.0) - 0.004;
    y_speed = ((rand() % 10) / 4500.0) - 0.004;
}

void Fries::move() {
    x += x_speed;
    y += y_speed;
}