#include "gun.hpp"

bullet::bullet(int SPEED, vec4 DIR) {
    speed = SPEED; dir = DIR;
    pNext = nullptr;
    pPrev = nullptr;
}

void gun::shoot() {
    bullet* newBullet = new bullet(10, dir);

    if (fired_tail == nullptr) {
        fired_head = fired_tail = newBullet;
        return;
    }

    fired_tail->pNext = newBullet;
    newBullet->pPrev = fired_tail;
    fired_tail = newBullet;
}

void gun::vanish(bullet* b) {
    bullet* prev = b->pPrev;
    bullet* next = b->pNext;
    delete b;

    if (prev != nullptr)
        prev->pNext = next;
    if (next != nullptr)
        next->pPrev = prev;
}

gun::gun() {
    fired_head = fired_tail = nullptr;
    up = down = left = right = false;
    speed = 5;
}

bullet::bullet() {};
bullet::~bullet() {};
gun::~gun() {};