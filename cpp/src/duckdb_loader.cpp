#include "duckdb_loader.hpp"
#include <iostream>
#include <sstream>
#include <filesystem>

DuckDBLoader::DuckDBLoader(const std::string& db_Path)
    : dbPath(db_Path) {
    try {
        if (!dbPath.empty()) {
            // Try to create parent directory if it doesn't exist
            std::filesystem::path p(dbPath);
            if (p.has_parent_path()) {
                std::filesystem::create_directories(p.parent_path());
            }
            db = std::make_unique<duckdb::DuckDB>(dbPath.c_str());
        } else {
            db = std::make_unique<duckdb::DuckDB>(nullptr);
        }
        conn = std::make_unique<duckdb::Connection>(*db);
        std::cout << "DuckDBLoader initialized with DB path: " << (dbPath.empty() ? "(memory)" : dbPath) << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "DuckDBLoader: failed to open DB at '" << dbPath << "' (" << e.what() << ") - falling back to in-memory DB" << std::endl;
        db = std::make_unique<duckdb::DuckDB>(nullptr);
        conn = std::make_unique<duckdb::Connection>(*db);
        dbPath.clear();
    }
}

bool DuckDBLoader::registerTicker(const std::string& folderPath,
                                  const std::string& ticker) {
    std::ostringstream ss;
    ss << "CREATE TABLE IF NOT EXISTS \"" << ticker << "\" AS SELECT * FROM read_parquet('"
       << folderPath << "/*.parquet');";
    auto res = runQuery(ss.str());
    if (!res) {
        std::cerr << "registerTicker: query returned null result" << std::endl;
        return false;
    }
#ifdef DUCKDB_HAS_QUERYRESULT_SUCCESS
    if (res->success) return true;
    std::cerr << "registerTicker error: " << res->error << std::endl;
    return false;
#else
    // Fallback: assume success if we got a non-null result
    return true;
#endif
}

duckdb::unique_ptr<duckdb::QueryResult> DuckDBLoader::runQuery(const std::string& sql) {
    if (!conn) return nullptr;
    return conn->Query(sql);
}

std::shared_ptr<arrow::Table> DuckDBLoader::toArrow(duckdb::QueryResult* result) {
    if (!result) return nullptr;
    std::cerr << "toArrow: Arrow conversion not implemented in this build; returning nullptr" << std::endl;
    return nullptr;
}