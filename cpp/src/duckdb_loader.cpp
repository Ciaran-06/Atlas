#include "duckdb_loader.hpp"
#include "duckdb/include/duckdb.hpp"

DuckDBLoader::DuckDBLoader(const std::string& db_Path) {
dbPath = db_Path;
duckdb::DuckDB db(dbPath);
}