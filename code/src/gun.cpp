#include "gun.hpp"

bullet::bullet(int SPEED, vec4 DIR) {
    speed = SPEED; dir = DIR;
    pNext = nullptr;
    pPrev = nullptr;
}

void gun::shoot() {
    bullet* newBullet = new bullet(10, RIGHT);
    newBullet->x = x;
    newBullet->y = y;

    if (fired_tail == nullptr) {
        fired_head = fired_tail = newBullet;
        return;
    }

    fired_tail->pNext = newBullet;
    newBullet->pPrev = fired_tail;
    fired_tail = newBullet;
}

gun::gun() {
    fired_head = fired_tail = nullptr;
    up = down = left = right = false;
    speed = 5;
    x = y = 0;
}
gun::~gun() {};

void gun::vanish(bullet* b) {

    if (b->pNext == nullptr) {
        fired_tail = nullptr;
        if (b->pPrev) 
            fired_tail = b->pPrev;
    }

    if (b->pPrev == nullptr) {
        fired_head = nullptr;
        if (b->pNext)
            fired_head = b->pNext;
    }

    delete b;
}

bullet::bullet() {};

bullet::~bullet() {    
    if (pPrev != nullptr)
        pPrev->pNext = pNext;
    if (pNext != nullptr)
        pNext->pPrev = pPrev;
}