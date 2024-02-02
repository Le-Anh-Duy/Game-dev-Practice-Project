#include "moving.hpp"

class bullet: public moving_with_arrows {
public:
    bullet* pNext;
    bullet* pPrev;
    bullet();
    ~bullet();
    bullet(int SPEED, vec4 DIR);
};

class gun: public moving_with_arrows {
public:
    bullet* fired_head;
    bullet* fired_tail;
    gun();
    ~gun();
    void vanish(bullet* b);
    void shoot();
};