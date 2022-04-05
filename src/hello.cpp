#include "hello.h"
#include <iostream>

extern "C" {
int add(int a, int b) {
    return a + b;
}


int main() {
    //std::cout << add(1, 2);
    return 0;
}
}