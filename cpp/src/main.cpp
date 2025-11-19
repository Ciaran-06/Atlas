#include <iostream>
#include "Engine.hpp"
#include "FileLoader.hpp"

int main() {
    std::cout << "ATLAS Engine Initialized" << std::endl;
    Engine engine;
    test t;
    engine.run();
    t.run();
    return 0;
}
