#include "moving.hpp"

moving_with_arrows::moving_with_arrows() {
    up = down = left = right = 0;
    speed = 0;
    dir = vec4(0, 0);
}

void moving_with_arrows::move() {
    if (dir.x == 0 && dir.y == 0) return;
    float ratio = 1.0 / dir.lenght();
    std::cout << "from " << x << ' ' << y << " with speed = " << speed << " with dir lenght = " << dir.lenght() << ' ';
    x += dir.x * speed * ratio; 
    y += dir.y * speed * ratio;
    std::cout << "Moved to " << x << ' ' << y << std::endl;
}

void moving_with_arrows::fixed_dir() {
    dir = vec4(0, 0);
    if (up) dir = add(dir, UP);
    if (down) dir = add(dir, DOWN);
    if (left) dir = add(dir, LEFT);
    if (right) dir = add(dir, RIGHT);
    // std::cout << up << ' ' << down << ' ' << left << ' ' << right << ' ' << dir.x << ' ' << dir.y << '\n';
}