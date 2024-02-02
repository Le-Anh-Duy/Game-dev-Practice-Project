#include "entities.hpp"
#include "vec4.hpp"

const vec4 UP = vec4(0, -1);
const vec4 DOWN = vec4(0, 1);
const vec4 LEFT = vec4(-1, 0);
const vec4 RIGHT = vec4(0, 1);

class moving_with_arrows: public entity {
public:
    bool up, down, left, right;
    int speed;
    vec4 dir;

    moving_with_arrows();
    void fixed_dir();
    void move();
};