#include <iostream>
#include "Engine.hpp"
#include "FileLoader.hpp"

int main() {
    std::cout << "ATLAS Engine Initialized: Version[0.0.1]" << std::endl;
    Engine engine;
    engine.run();

    CSVLoader loader("../../data/raw");
    return 0;
}
