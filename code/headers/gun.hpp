#include "moving.hpp"

class bullet: public moving_with_arrows {
public:
    bullet* pNext;
    bullet* pPrev;
    bullet(int SPEED, vec4 DIR);
    bullet();
    ~bullet();
};

class gun: public moving_with_arrows {
public:
    bullet* fired_head;
    bullet* fired_tail;
    gun();
    ~gun();
    void shoot();
    void vanish(bullet* b);
};