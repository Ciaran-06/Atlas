#include <iostream>
#include "Engine.hpp"
#include "duckdb_loader.hpp"

int main() {
    std::cout << "ATLAS Engine Initialized: Version[0.0.1]" << std::endl;
    Engine engine;
    engine.run();

    DuckDBLoader loader("../../data/duckdb/main.db");
    

    return 0;
}
