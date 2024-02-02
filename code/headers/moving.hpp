#include "entities.hpp"
#include "vec4.hpp"

const vec4 UP = vec4(0, -1);
const vec4 DOWN = vec4(0, 1);
const vec4 LEFT = vec4(-1, 0);
const vec4 RIGHT = vec4(1, 0);

class moving_with_arrows: public entity {
public:
    bool up, down, left, right; // check if the current vector has any of the fours vectors
    int speed;
    vec4 dir;

    moving_with_arrows();
    void fixed_dir(); // fix the direction vector to the right angle by doing addition of every possible unit vector
    void move(); // move by x, y value
};