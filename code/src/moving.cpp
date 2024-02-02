#include "moving.hpp"

moving_with_arrows::moving_with_arrows() {
    up = down = left = right = 0;
    speed = 0;
    dir = vec4(0, 0);
}

void moving_with_arrows::move() {
    
    float ratio = 1.0 / dir.lenght();
    
    x += dir.x * speed * ratio; 
    y += dir.y * speed * ratio;
}

void moving_with_arrows::fixed_dir() {
    dir = vec4(0, 0);
    if (up) dir = add(dir, UP);
    if (down) dir = add(dir, DOWN);
    if (left) dir = add(dir, LEFT);
    if (right) dir = add(dir, RIGHT);
}