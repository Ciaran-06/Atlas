#include "duckdb_loader.hpp"


const std::string dbPath  = "../data/duckdb/main.db";

DuckDBLoader::DuckDBLoader(const std::string& db_Path) {
    std::cout << "DuckDBLoader initialized with DB path: " << db_Path << std::endl;
}