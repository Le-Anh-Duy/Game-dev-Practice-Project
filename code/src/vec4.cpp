#include "vec4.hpp"
#include <cmath>

vec4::vec4() {
    x = 0; y = 0;
}

vec4::vec4(float x, float y): x(x), y(y) {};

vec4 add(vec4 a, vec4 b) {
    return vec4(a.x + b.x, a.y + b.y);
}

vec4 sub(vec4 a, vec4 b) {
    return vec4(a.x - b.x, a.y - b.y);
}

vec4 mull(vec4 a, float k) {
    return vec4(a.x * k, a.y * k);
}

float vec4::lenght() {
    return sqrt(x * x + y * y);
}

float dot(vec4 a, vec4 b) {
    return a.x * b.y + b.x * a.y;
}

float lenght(vec4 a) {
    return sqrt(a.x * a.x + a.y * a.y);
}


