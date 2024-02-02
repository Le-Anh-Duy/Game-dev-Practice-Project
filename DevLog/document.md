# This gonna be my documents
## 1. Overlook
    a blog about some basic concepts
    https://stackoverflow.com/questions/21007329/what-is-an-sdl-renderer/21007477#21007477
## 2. Renderer problems
    need to render on only one renderer
## 3. Destructor bug
```c++, numberLines
#include <deque>
#include <iostream>

using namespace std;

class P {
public:
    void func();
    P();
    ~P();
};

class test : public P {
public:
    int x;
    int* s ;
    ~test() {
        std::cout << "calling" << x << '\n';
    };

    test() {

    };
};

P::P() {

}

test* gun = new test;

P::~P() {
    delete gun;
}

std::deque <test*> d;

int main() {
    
    P* x = new P;
    delete gun;

    return 0;
}

```

this will generate an infinite loop, by somehow, the problem is, we call `delete gun;` at line 41, it will also call destructor `~P()`, so repeatively it will start a loop by calling `delete gun;` again, but at line 33