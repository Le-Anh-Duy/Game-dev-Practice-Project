#include <iostream>

struct vec4 {
    float x, y;
    vec4();
    vec4(float x, float y);
    float lenght();
};  

vec4 add(vec4 a, vec4 b);
vec4 sub(vec4 a, vec4 b);
vec4 mull(vec4 a, float k);
float dot(vec4 a, vec4 b);
float lenght(vec4 a);